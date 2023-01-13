#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>

typedef struct{
    int produced_items;
    sem_t p_mutex;
    int tail;
} producer_info;

typedef struct{
    int consumed_items;
    sem_t c_mutex;
    int head;
    int tail_final;
    int *final_queue;
} consumer_info;

int *array_;
int capacity;
sem_t empty_;
sem_t full;
int augmenting_factor;

void **initialize(pthread_t **, pthread_t **, int, int);
void *producer(void *);
void *consumer(void *);
int product_transformation(int);
void sigalarm_manager(int);

int main(int argc, char **argv){    // format is argv[0] n_producers n_consumers queue_capacity duration_in_seconds augmenting_factor
    signal(SIGALRM, sigalarm_manager);
    srand(time(0));
    capacity = atoi(argv[3]);
    int n_producers = atoi(argv[1]);
    int n_consumers = atoi(argv[2]);
    int duration = atoi(argv[4]);
    augmenting_factor = atoi(argv[5]);
    pthread_t *p_tids;
    pthread_t *c_tids;
    void **structures = initialize(&p_tids, &c_tids, n_producers, n_consumers);
    producer_info *p = (producer_info *) structures[0];
    consumer_info *c = (consumer_info *) structures[1];
    alarm(duration);
    for(int i = 0; i < n_producers; i++){
        sleep(rand() % 3);
        pthread_create(p_tids + i, NULL, producer, (void *) p);
    }
    for(int i = 0; i < n_consumers; i++){
        sleep(rand() % 3);
        pthread_create(c_tids + i, NULL, consumer, (void *) c);
    }
    pause();
    for(int i = 0; i < n_producers; i++)
        pthread_cancel(p_tids[i]);
    for(int i = 0; i < n_consumers; i++)
        pthread_cancel(c_tids[i]);
    fprintf(stdout, "\nproduced items: %d\nconsumed items: %d\nfinal queue: ", p->produced_items, c->consumed_items);
    for(int i = 0; (c->final_queue[i] > 0 && i < augmenting_factor * capacity); i++)
        fprintf(stdout, "%d ", c->final_queue[i]);
    fprintf(stdout, "\n");
    return 0;
}

void **initialize(pthread_t **p_tids, pthread_t **c_tids, int n_producers, int n_consumers){
    producer_info *p = (producer_info *) malloc(sizeof(producer_info));
    p->produced_items = 0;
    consumer_info *c = (consumer_info *) malloc(sizeof(consumer_info));
    c->consumed_items = 0;
    p->tail = 0;
    c->head = 0;
    c->final_queue = (int *) malloc(augmenting_factor * capacity * sizeof(int));
    c->tail_final = 0;
    *p_tids = (pthread_t *) malloc(n_producers * sizeof(pthread_t));
    *c_tids = (pthread_t *) malloc(n_consumers * sizeof(pthread_t));
    sem_init(&full, 0, 0);
    sem_init(&empty_, 0, capacity);
    sem_init(&(p->p_mutex), 0, 1);
    sem_init(&(c->c_mutex), 0, 1);
    array_ = (int *) malloc(capacity * sizeof(int));
    void **structures = (void **) malloc(2 * sizeof(void *));
    structures[0] = (void *) p;
    structures[1] = (void *) c;
    return structures;
}

void *producer(void *p_){
    srand(time(0));
    producer_info *p = (producer_info *) p_;
    int new_product;
    while(36){
        sleep(rand() % 11);
        sem_wait(&(p->p_mutex));
        sem_wait(&empty_);
        new_product = 1 + rand() % 10;
        array_[p->tail] = new_product;
        p->produced_items++;
        fprintf(stdout, "\nthread %lu generates product %d\n", pthread_self(), new_product);
        p->tail = (p->tail + 1) % capacity;
        sem_post(&full);
        sem_post(&(p->p_mutex));
    }
    pthread_exit(0);
}

void *consumer(void *c_){
    srand(time(0));
    consumer_info *c = (consumer_info *) c_;
    int new_product;
    while(36){
        sleep(rand() % 11);
        sem_wait(&(c->c_mutex));
        sem_wait(&full);
        new_product = array_[c->head];
        int transformed_product = product_transformation(new_product);
        c->consumed_items++;
        fprintf(stdout, "\nthread %lu transforms product %d int product %d\n", pthread_self(), new_product, transformed_product);
        c->head = (c->head + 1) % capacity;
        c->final_queue[c->tail_final] = transformed_product;
        c->tail_final = (c->tail_final + 1) % (augmenting_factor * capacity);
        sem_post(&empty_);
        sem_post(&(c->c_mutex));
    }
    pthread_exit(0);
}

int product_transformation(int old_product){
    return old_product * old_product;
}

void sigalarm_manager(int signo){
    fprintf(stdout, "\nprocess completed!\n");
}