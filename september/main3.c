#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define N_THREADS 4

enum chars{PLUS, MINUS, STAR, NEWLINE};
pthread_mutex_t locks[N_THREADS];
int counters[N_THREADS];
pthread_t ids[N_THREADS];
int global_counter = PLUS;
int N;

void initialize_locks();
void initialize_counters();
void initialize_functions_array();
void *(*functions_array[N_THREADS])(void *);
void *TP(void *);
void *TM(void *);
void *TS(void *);
void *TNL(void *);

int main3(int n){
    initialize_locks();
    initialize_counters();
    initialize_functions_array();
    N = n;
    for(int i = 0; i < N_THREADS; i++)
        pthread_create(ids + i, NULL, functions_array[i], NULL);
    for(int i = 0; i < N_THREADS; i++)
        pthread_join(*(ids + i), NULL);
    return 0;
}

void initialize_locks(){
    for(int i = 0; i < N_THREADS; i++){
        pthread_mutex_init(locks + i, NULL);
        if(i > PLUS)
            pthread_mutex_lock(locks + i);
    }
}

void initialize_counters(){
    for(int i = 0; i < N_THREADS; i++)
        counters[i] = 0;
}

void initialize_functions_array(){
    functions_array[PLUS] = TP;
    functions_array[MINUS] = TM;
    functions_array[STAR] = TS;
    functions_array[NEWLINE] = TNL;
}

void *TP(void *NULL_){
    pthread_detach(pthread_self());
    while(36){
        pthread_mutex_lock(locks + PLUS);
        printf("+");
        counters[PLUS]++;
        if(counters[PLUS] == N){
            counters[PLUS] = 0;
            pthread_mutex_unlock(locks + NEWLINE);
        }else
            pthread_mutex_unlock(locks + PLUS);
    }
}

void *TM(void *NULL_){
    pthread_detach(pthread_self());
    while(36){
        pthread_mutex_lock(locks + MINUS);
        printf("-");
        counters[MINUS]++;
        if(counters[MINUS] == N){
            counters[MINUS] = 0;
            pthread_mutex_unlock(locks + NEWLINE);
        }else
            pthread_mutex_unlock(locks + MINUS);
    }
}

void *TS(void *NULL_){
    pthread_detach(pthread_self());
    while(36){
        pthread_mutex_lock(locks + STAR);
        printf("*");
        counters[STAR]++;
        if(counters[STAR] == N){
            counters[STAR] = 0;
            pthread_mutex_unlock(locks + NEWLINE);
        }else
            pthread_mutex_unlock(locks + STAR);
    }
}

void *TNL(void *NULL_){
    pthread_detach(pthread_self());
    while(36){
        pthread_mutex_lock(locks + NEWLINE);
        printf("\n");
        switch(global_counter){
            case PLUS:
                global_counter = MINUS;
                pthread_mutex_unlock(locks + MINUS);
                break;
            case MINUS:
                global_counter = STAR;
                pthread_mutex_unlock(locks + STAR);
                break;
            case STAR:
                global_counter = PLUS;
                pthread_mutex_unlock(locks + PLUS);
                break;
            default:
                return NULL;
        }
    }
}