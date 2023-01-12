#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

#define N_MUTEXES 5
#define MUTEX_ABC 0
#define MUTEX_D 1

#define N_THREADS 4

int main1(int, char *);

int main3(int);
sem_t semaphores[N];
int counters[N];
int n_threads;
pthread_mutex_t counters_mutex;
void wait_ch(int);
void signal_ch(int);
void initialize_semaphores();
void initialize_counters();
void *run_thread(void *);

int main4();
void initialize_mutexes();
void initialize_thread_array();
void *TA(void *);
void *TB(void *);
void *TC(void *);
void *TD(void *);
pthread_mutex_t mutexes[N_MUTEXES];
void *(*thread_array[N_THREADS])(void *);
int n_c;

int main(int argc, char **argv){
    int ex = atoi(argv[1]);
    switch(ex){
        case 1:
            return main1(atoi(argv[2]), argv[0]);
        case 3:
            return main3(atoi(argv[2]));
        case 4:
            return main4();
        default:
            return -1;
    }
}

int main1(int n, char *argv_0){
    char str[100];
    setbuf(stdout, 0);
    if(n > 0){
        fork();
        if(fork()){
            printf("\nX\n");
            sprintf(str, "%s %d %d", argv_0, 1, n - 1);
            system(str);
        }
    }
    return 0;
}

int main3(int n_threads){
    srand(time(0));
    initialize_semaphores();
    initialize_counters();
    pthread_mutex_init(&counters_mutex, NULL);
    pthread_t *thread_ids = (pthread_t *) malloc(n_threads * sizeof(pthread_t));
    for(int i = 0; i < n_threads; i++){
        pthread_create(thread_ids + i, NULL, run_thread, NULL);
        sleep(rand() % 6);
    }
    for(int i = 0; i < n_threads; i++)
        pthread_join(thread_ids[i], NULL);
    return 0;
}
void initialize_semaphores(){
    for(int i = 0; i < N; i++)
        sem_init(semaphores + i, 0, 0);
}
void initialize_counters(){
    for(int i = 0; i < N; i++)
        counters[i] = 0;
}
void *run_thread(void *NULL_){
    srand(time(0));
    void (*choices[2])(int);
    choices[0] = wait_ch;
    choices[1] = signal_ch;
    choices[rand() % 2](rand() % N);
    pthread_exit(0);
}
void wait_ch(int x){
    pthread_mutex_lock(&counters_mutex);
    counters[x]++;
    pthread_mutex_unlock(&counters_mutex);
    fprintf(stdout, "\n%lu - wait %d\n", pthread_self(), x);
    sem_wait(semaphores + x);
    fprintf(stdout, "\n%lu - unlocked %d\n", pthread_self(), x);
}
void signal_ch(int x){
    fprintf(stdout, "\n%lu - signal %d\n", pthread_self(), x);
    pthread_mutex_lock(&counters_mutex);
    int flag = (counters[x] == 0);
    pthread_mutex_unlock(&counters_mutex);
    if(flag)
        return;
    for(int i = 0; i < counters[x]; i++)
        sem_post(semaphores + x);
    pthread_mutex_lock(&counters_mutex);
    counters[x] = 0;
    pthread_mutex_unlock(&counters_mutex);
}

int main4(){
    initialize_mutexes();
    initialize_thread_array();
    n_c = 0;
    pthread_t *thread_ids = (pthread_t *) malloc(N_THREADS * sizeof(pthread_t));
    for(int i = 0; i < N_THREADS; i++)
        pthread_create(thread_ids + i, NULL, thread_array[i], NULL);
    for(int i = 0; i < N_THREADS; i++)
        pthread_join(thread_ids[i], NULL);
    return 0;
}
void initialize_mutexes(){
    for(int i = 0; i < N_THREADS; i++)
        pthread_mutex_init(mutexes + i, NULL);
    pthread_mutex_lock(mutexes + MUTEX_D);
}
void initialize_thread_array(){
    thread_array[0] = TA;
    thread_array[1] = TB;
    thread_array[2] = TC;
    thread_array[3] = TD;
}
void *TA(void *NULL_){
    while(36){
        pthread_mutex_lock(mutexes + MUTEX_ABC);
        fprintf(stdout, "A");
        pthread_mutex_unlock(mutexes + MUTEX_ABC);
    }
    pthread_exit(0);
}
void *TB(void *NULL_){
    while(36){
        pthread_mutex_lock(mutexes + MUTEX_ABC);
        fprintf(stdout, "B");
        pthread_mutex_unlock(mutexes + MUTEX_D);
    }
    pthread_exit(0);
}
void *TC(void *NULL_){
    while(36){
        pthread_mutex_lock(mutexes + MUTEX_ABC);
        fprintf(stdout, "C");
        pthread_mutex_unlock(mutexes + MUTEX_D);
    }
    pthread_exit(0);
}
void *TD(void *NULL_){
    while(36){
        pthread_mutex_lock(mutexes + MUTEX_D);
        if(n_c == 2){
            fprintf(stdout, "D\n");
            n_c = 0;
            pthread_mutex_unlock(mutexes + MUTEX_ABC);
        }else{
            fprintf(stdout, "D");
            n_c++;
            pthread_mutex_unlock(mutexes + MUTEX_D);
        }
    }
    pthread_exit(0);
}