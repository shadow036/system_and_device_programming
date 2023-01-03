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
};

data_t *generate_thread_parameters(char *queue, int capacity, int *head, int *tail){
  data_t *d = (data_t *) malloc(sizeof(data_t));
  d->queue = queue;
  d->capacity = capacity;
  d->head = head;
  d->tail = tail;
  sem_t f, e;
  sem_init(&f, 0, 0);
  sem_init(&e, 0, capacity);
  d->is_full = &f;
  d->is_empty = &e;
  return d;
}

void *producer(void *parameter){
  srand(time(0));
  data_t *d = (data_t *) parameter;
  while(36){
    sleep(rand() % 5);
    sem_wait(d->is_empty);
    char product = 97 + rand() % 26;
    d->queue[*(d->tail)] = product;
    *(d->tail) = (*(d->tail) + 1) % (d->capacity);
    fprintf(stdout, "\nPRODUCER: %c\n", product);
    sem_post(d->is_full);
  }
}

void *consumer(void *parameter){
  srand(time(0));
  data_t *d = (data_t *) parameter;
  while(36){
    sleep(rand() % 5);
    sem_wait(d->is_full);
    char product = d->queue[*(d->head)];
    *(d->head) = (*(d->head) + 1) % (d->capacity);
    fprintf(stdout, "\nCONSUMER: %c\n", product);
    sem_post(d->is_empty);
  }
}
