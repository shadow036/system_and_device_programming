#include "public.h"
#include <string.h>

pthread_mutex_t *generate_mutex();

struct lr_s{
    pthread_mutex_t *local_mutex;
    pthread_mutex_t *global_mutex;
    int *lr_amount;
    char message[100];
};

struct rl_s{
    pthread_mutex_t *local_mutex;
    pthread_mutex_t *global_mutex;
    int *rl_amount;
    char message[100];
};

pthread_mutex_t *generate_mutex(){
    pthread_mutex_t *m = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(m, NULL);
    return m;
}

lr_t *generate_lr(int *lr_amount){
    lr_t *lr = (lr_t *) malloc(sizeof(lr_t));
    lr->lr_amount = lr_amount;
    lr->local_mutex = generate_mutex();
    lr->global_mutex = generate_mutex();
    strcpy(lr->message, "\nmoving from left to right\n");
    return lr;
}

rl_t *generate_rl(int *rl_amount, lr_t *lr){
    rl_t *rl = (rl_t *) malloc(sizeof(rl_t));
    rl->rl_amount = rl_amount;
    rl->local_mutex = generate_mutex();
    rl->global_mutex = lr->global_mutex;
    strcpy(rl->message, "\nmoving from right to left\n");
    return rl;
}

void *move_lr(void *p){
    lr_t *p2 = (lr_t *) p;
    pthread_mutex_lock(p2->local_mutex);
    *(p2->local_mutex)++;
    if(*(p2->lr_amount) == 1)
        pthread_mutex_lock(p2->global_mutex);
    pthread_mutex_unlock(p2->local_mutex);
    write(STDOUT_FILENO, p2->message, 100);
    pthread_mutex_lock(p2->local_mutex);
    *(p2->local_mutex)--;
    if(*(p2->lr_amount) == 0)
        pthread_mutex_unlock(p2->global_mutex);
    pthread_mutex_unlock(p2->local_mutex);
    pthread_exit(0);
}

void *move_rl(void *p){
    rl_t *p2 = (rl_t *) p;
    pthread_mutex_lock(p2->local_mutex);
    *(p2->local_mutex)++;
    if(*(p2->rl_amount) == 1)
        pthread_mutex_lock(p2->global_mutex);
    pthread_mutex_unlock(p2->local_mutex);
    write(STDOUT_FILENO, p2->message, 100);
    pthread_mutex_lock(p2->local_mutex);
    *(p2->local_mutex)--;
    if(*(p2->rl_amount) == 0)
        pthread_mutex_unlock(p2->global_mutex);
    pthread_mutex_unlock(p2->local_mutex);
    pthread_exit(0);
}
