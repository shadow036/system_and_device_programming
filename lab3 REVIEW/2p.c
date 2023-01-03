/*
Exercise 02
Memory mapped I/O
-----------------

A binary file has the content specified by laboratory 02, exercise 01,
i.e.:

1 100000 Romano Antonio 25
2 150000 Fabrizi Aldo 22
3 200000 Verdi Giacomo 15
4 250000 Rossi Luigi 30

Write a C program that:
- Maps the file into memory.
- Runs two threads:
  - The first thread visits the records from the first to the last one
    and increases the second field (the register number) by 1.
  - The second thread visits the records from the last one to the first one
    and decreases the last field (the mark) by 1.
*/

#include "2.h"
#include <stdlib.h>

#define ID_SIZE sizeof(int)
#define REGISTER_SIZE sizeof(long)
#define NAME_LENGTH 30 + 1
#define SURNAME_LENGTH 30 + 1
#define MARK_SIZE sizeof(int)

struct data_s{
    void *mapped_memory;
    int size;
};

void *register_increaser(void *p){
    void *mapped_memory = ((data_t *) p)->mapped_memory;
    int size = ((data_t *) p)->size;
    int offset = ID_SIZE;
    while(offset < size){
        long *register_ = (long *) (mapped_memory + offset);
        *register_ = (*register_) + 1;
        offset += (ID_SIZE + REGISTER_SIZE + NAME_LENGTH + SURNAME_LENGTH + MARK_SIZE);
    }
    pthread_exit(0);
}

void *mark_decreaser(void *p){
    void *mapped_memory = ((data_t *) p)->mapped_memory;
    int size = ((data_t *) p)->size;
    int offset = size - MARK_SIZE;
    while(offset > 0){
        int *mark = (int *) (mapped_memory + offset);
        *mark = (*mark) - 1;
        offset -= (ID_SIZE + REGISTER_SIZE + NAME_LENGTH +SURNAME_LENGTH + MARK_SIZE);
    }
    pthread_exit(0);
}

void *map_memory(char *filename, int *size, int *fd){
    *fd = open(filename, O_RDWR);
    struct stat buffer;
    fstat(*fd, &buffer);
    *size = buffer.st_size;
    void *mapped_memory = mmap(0, *size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, *fd, 0);
    return mapped_memory;
}

data_t *generate_data(void *mapped_memory, int size){
    data_t *d = (data_t *) malloc(sizeof(data_t));
    d->mapped_memory = mapped_memory;
    d->size = size;
    return d;
}
