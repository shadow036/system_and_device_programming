#include "public.h"
#include <stdio.h>
#include <semaphore.h>
#include <time.h>

struct reader_s{
    int *active_readers;
    sem_t *reader_mutex;
    sem_t *reader_semaphore;
    sem_t *writer_semaphore;
};

struct writer_s{
    int *active_writers;
    sem_t *writer_mutex;
    sem_t *reader_semaphore;
    sem_t *writer_semaphore;
};

reader_t *generate_reader_structure(int *active_readers){
    reader_t *reader = (reader_t *) malloc(sizeof(reader_t));
    reader->active_readers= active_readers;
    sem_t m;
    sem_t r;
    sem_t w;
    sem_init(&m, 0, 1);
    sem_init(&r, 0, 1);
    sem_init(&w, 0, 1);
    reader->reader_mutex = &m;
    reader->reader_semaphore = &r;
    reader->writer_semaphore = &w;
    return reader;
}

writer_t *generate_writer_structure(int *active_writers, reader_t *reader){
    writer_t *writer = (writer_t *) malloc(sizeof(writer_t));
    sem_t m;
    sem_init(&m, 0, 1);
    writer->writer_mutex = &m;
    writer->reader_semaphore = reader->reader_semaphore;
    writer->writer_semaphore = reader->writer_semaphore;
    writer->active_writers = active_writers;
    return writer;
}

void *reader(void *p){
    reader_t *r = (reader_t *) p;
    srand(time(0));
    while(36){
        sleep(rand() % 10);
        sem_wait(r->reader_semaphore);
        sem_wait(r->reader_mutex);
        (*(r->active_readers))++;
        if(*(r->active_readers) == 1)
            sem_wait(r->writer_semaphore);
        sem_post(r->reader_mutex);
        sem_post(r->reader_semaphore);
        fprintf(stdout, "\nreading... (id: %lu)\n", pthread_self());
        sem_wait(r->reader_mutex);
        (*(r->active_readers))--;
        if(*(r->active_readers) == 0)
            sem_post(r->writer_semaphore);
        sem_post(r->reader_mutex);
    }
    pthread_exit(0);
}

void *writer(void *p){
    writer_t *w = (writer_t *) p;
    srand(time(0));
    while(36){
        sleep(rand() % 10);
        sem_wait(w->writer_mutex);
        (*(w->active_writers))++;
        if(*(w->active_writers) == 1)
            sem_wait(w->reader_semaphore);
        sem_post(w->writer_mutex);
        sem_wait(w->writer_semaphore);
        fprintf(stdout, "\nwriting... (id: %lu)\n", pthread_self());
        sem_post(w->writer_semaphore);
        sem_wait(w->writer_mutex);
        (*(w->active_writers))--;
        if(*(w->active_writers) == 0)
            sem_post(w->reader_semaphore);
        sem_post(w->writer_mutex);
    }
    pthread_exit(0);
}
