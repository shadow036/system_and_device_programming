#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>

typedef struct{
    int index;
} thread_parameter;

pthread_cond_t condition_variable_;
pthread_mutex_t mutex;
int completed_threads;
int total_threads;
sem_t *semaphores;
pthread_t *thread_ids;

void initialize();
void *worker(void *);
void barrier();
thread_parameter *generate_thread_parameter(int);

int main(int argc, char **argv){
    srand(time(0));
    total_threads = atoi(argv[1]);
    initialize();
    for(int i = 0; i < total_threads; i++){
        pthread_create(thread_ids + i, NULL, worker, generate_thread_parameter(i));
        pthread_detach(thread_ids[i]);
        sleep(rand() % 6);
    }
    barrier();
    pthread_exit(0);
}

void initialize(){
    pthread_cond_init(&condition_variable_, NULL);
    pthread_mutex_init(&mutex, NULL);
    completed_threads = 0;
    semaphores = (sem_t *) malloc(total_threads * sizeof(sem_t));
    for(int i = 0; i < total_threads; i++)
        sem_init(semaphores + i, 0, 0);
    thread_ids = (pthread_t *) malloc(total_threads * sizeof(pthread_t));
}

void *worker(void *p_){
    int index = ((thread_parameter *) p_)->index;
    pthread_mutex_lock(&mutex); // used to protect "completed_threads", not necessary otherwise
    completed_threads++;
    fprintf(stdout, "\nthread %lu completed\n", pthread_self());
    pthread_cond_signal(&condition_variable_);
    pthread_mutex_unlock(&mutex);
    sem_wait(semaphores + index);
    fprintf(stdout, "\nthread %lu passed through the barrier\n", pthread_self());
    pthread_exit(0);
}

void barrier(){
    pthread_mutex_lock(&mutex);
    while(completed_threads < total_threads)
        pthread_cond_wait(&condition_variable_, &mutex);
    pthread_mutex_unlock(&mutex);
    for(int i = 0; i < total_threads; i++)
        sem_post(semaphores + i);
}

thread_parameter *generate_thread_parameter(int index){
    thread_parameter *p = (thread_parameter *) malloc(sizeof(thread_parameter));
    p->index = index;
    return p;
}