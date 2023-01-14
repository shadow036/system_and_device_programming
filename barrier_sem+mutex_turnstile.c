/*
Describe how it is possible to implement the function pthread_barrier_wait with semaphores, mutexes,
and counters.
*/

#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int total_threads;
int active_threads;
pthread_mutex_t mutex;
sem_t semaphore;
pthread_t *thread_ids;

void initialize(void);
void *worker(void *);

int main(int argc, char **argv){
    srand(time(0));
    total_threads = atoi(argv[1]);
    initialize();
    for(int i = 0; i < total_threads; i++){
        pthread_create(thread_ids + i, NULL, worker, NULL);
        pthread_detach(pthread_self());
        sleep(rand() % 6);
    }
    pthread_exit(0);
}

void initialize(){
    active_threads = 0;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaphore, 0, 0);
    thread_ids = (pthread_t *) malloc(total_threads * sizeof(pthread_t));
}

void *worker(void *NULL_){
    pthread_mutex_lock(&mutex);
    active_threads++;
    fprintf(stdout, "\nthread %lu is active\n", pthread_self());
    if(active_threads == total_threads)
        sem_post(&semaphore);
    pthread_mutex_unlock(&mutex);
    sem_wait(&semaphore);
    fprintf(stdout, "\nthread %lu passes the barrier\n", pthread_self());
    sem_post(&semaphore);
    pthread_exit(0);
}