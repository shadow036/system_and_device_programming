#include "public.h"
#include <semaphore.h>
#include <stdio.h>

struct data_reader_s{
    int *active_readers;
    sem_t *reader_mutex;
    sem_t *writer_semaphore;
};

struct data_writer_s{
    sem_t *writer_semaphore;
};

data_reader_t *generate_reader_structure(int *active_readers, data_writer_t *w){
    data_reader_t *r = (data_reader_t *) malloc(sizeof(data_reader_t));
    r->active_readers = active_readers;
    sem_t m;
    sem_init(&m, 0, 1);
    r->reader_mutex = &m;
    r->writer_semaphore = w->writer_semaphore;
    return r;
}

data_writer_t *generate_writer_structure(){
    data_writer_t *w = (data_writer_t *) malloc(sizeof(data_writer_t));
    sem_t ws;
    sem_init(&ws, 0, 1);
    w->writer_semaphore = &ws;
    return w;
}

void *reader(void *p){
    data_reader_t *r = (data_reader_t *) p;
    while(36){
        sem_wait(r->reader_mutex);
        *(r->active_readers)++;
        if(*(r->active_readers) == 1)
            sem_wait(r->writer_semaphore);
        sem_post(r->reader_mutex);
        fprintf(stdout, "\nreading... (id: %lu)\n", pthread_self());
        sem_wait(r->reader_mutex);
        *(r->active_readers)--;
        if(*(r->active_readers) == 0)
            sem_post(r->writer_semaphore);
        sem_post(r->reader_mutex);
    }
    pthread_exit(0);
}

void *writer(void *p){
    data_writer_t *w = (data_writer_t *) p;
    while(36){
        sem_wait(w->writer_semaphore);
        fprintf(stdout, "\nwriting... (id: %lu)\n", pthread_self());
        sem_post(w->writer_semaphore);
    }
    pthread_exit(0);
}
