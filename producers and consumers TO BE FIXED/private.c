#include "public.h"
#include <semaphore.h>
#include <time.h>
#include <stdio.h>

struct data_s{
    char *queue;
    int capacity;
    int *head;
    int *tail;
    sem_t *is_full;
    sem_t *is_empty;
    sem_t *producers_mutex;
    sem_t *consumers_mutex;
    sem_t *
    int *number_of_producers;
    int *number_of_consumers;
};

data_t *generate_thread_parameters(char *queue, int capacity, int *head, int *tail, int *number_of_producers, int *number_of_consumers){
    data_t *d = (data_t *) malloc(sizeof(data_t));
    d->queue = queue;
    d->capacity = capacity;
    d->head = head;
    d->tail = tail;
    sem_t f, e, p, c;
    sem_init(&f, 0, 0);
    sem_init(&e, 0, capacity);
    sem_init(&p, 0, 1);
    sem_init(&c, 0, 1);
    d->is_full = &f;
    d->is_empty = &e;
    d->producers_mutex = &p;
    d->consumers_mutex = &c;
    d->number_of_producers = number_of_producers;
    d->number_of_consumers = number_of_consumers;
    return d;
}

void *producers(void *p){
    srand(time(0));
    data_t *d = (data_t *) p;
    while(36){
        sleep(rand() % 10);
        *(d->number_of_producers)++;
        sem_
        if(*(d->number_of_producers) == 1)
          sem_wait(d->producers_mutex);
        else
          sem_wait(d->producers_mutex);
        sem_wait(d->is_empty);
        char product = 97 + rand() % 26;
        d->queue[*(d->tail)] = product;
        *(d->tail) = (*(d->tail) + 1) % (d->capacity);
        fprintf(stdout, "\nPRODUCER: %c\n", product);
        sem_post(d->is_full);
        *(d->number_of_producers)--;
        if(*(d->number_of_producers) == 0)
          sem_post(d->producers_mutex);
    }
}

void *consumers(void *p){
    srand(time(0));
    data_t *d = (data_t *) p;
    while(36){
        sleep(rand() % 10);
        sem_wait(d->consumers_mutex);
        sem_wait(d->is_full);
        char product = d->queue[*(d->head)];
        *(d->head) = (*(d->head) + 1) % (d->capacity);
        fprintf(stdout, "\nCONSUMER: %c\n", product);
        sem_post(d->is_empty);
        sem_post(d->consumers_mutex);
    }
}
