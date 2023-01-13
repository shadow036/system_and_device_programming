#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N_THREADS 100

pthread_t tids[N_THREADS];
sem_t s;
pthread_mutex_t m;
int threads_in_the_bottleneck;

void *t(void *);
void bottleneck();
void initialize();

int main(){
    initialize();
    for(int i = 0; i < N_THREADS; i++)
        pthread_create(tids + i, NULL, t, NULL);
    sleep(1);
    pthread_exit(0);
}

void *t(void *){
    pthread_detach(pthread_self());
    sem_wait(&s);
    pthread_mutex_lock(&m);
    threads_in_the_bottleneck++;
    pthread_mutex_unlock(&m);
    bottleneck();
    pthread_mutex_lock(&m);
    threads_in_the_bottleneck--;
    pthread_mutex_unlock(&m);
    sem_post(&s);
    pthread_exit(0);
}

void bottleneck(){
    sleep(5);
    printf("\nthread %lu is currently in the bottleneck along with other %d threads\n", pthread_self(), threads_in_the_bottleneck - 1);
}

void initialize(){
    sem_init(&s, 0, 5);
    pthread_mutex_init(&m, NULL);
    threads_in_the_bottleneck = 0;
}