#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

void initialize();
void *lr(void *);
void *rl(void *);

sem_t lr_mutex;
sem_t rl_mutex;
sem_t busy;
int n_active_lr;
int n_active_rl;

int main(int argc, char **argv){
    int n_lr = atoi(argv[1]);
    int n_rl = atoi(argv[2]);
    initialize();
    pthread_t *tids = (pthread_t *) malloc((n_lr + n_rl) * sizeof(pthread_t));
    for(int i = 0; i < (n_lr + n_rl); i++){
        sleep(1);
        if(i < n_lr)
            pthread_create(tids + i, NULL, lr, NULL);
        else
            pthread_create(tids + i, NULL, rl, NULL);
        pthread_detach(tids[i]);
    }
    free(tids);
    sleep(1);
    return 0;
}

void initialize(){
    n_active_lr = 0;
    n_active_rl = 0;
    sem_init(&lr_mutex, 0, 1);
    sem_init(&rl_mutex, 0, 1);
    sem_init(&busy, 0, 1);
}

void *lr(void *NULL_){
    sleep(rand() % 5);
    sem_wait(&lr_mutex);
    n_active_lr++;
    if(n_active_lr == 1)
        sem_wait(&busy);
    sem_post(&lr_mutex);
    printf("\nvehicle passing from left to right\n");
    sleep(1);
    sem_wait(&lr_mutex);
    n_active_lr--;
    if(n_active_lr == 0)
        sem_post(&busy);
    sem_post(&lr_mutex);
    pthread_exit(0);
}

void *rl(void *NULL_){
    sleep(rand() % 5);
    sem_wait(&rl_mutex);
    n_active_rl++;
    if(n_active_rl == 1)
        sem_wait(&busy);
    sem_post(&rl_mutex);
    printf("\nvehicle passing from right to left\n");
    sleep(1);
    sem_wait(&rl_mutex);
    n_active_rl--;
    if(n_active_rl == 0)
        sem_post(&busy);
    sem_post(&rl_mutex);
    pthread_exit(0);
}
