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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>

typedef struct data_s data_t;

void *register_increaser(void *);
void *mark_decreaser(void *);
void *map_memory(char *, int *, int *);
data_t *generate_data(void *, int);
