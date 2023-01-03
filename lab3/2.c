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
#include <stdio.h>

int main(int argc, char **argv){
    if(argc != 2){
        write(STDOUT_FILENO, "wrong number of parameters", sizeof("wrong number of parameters"));
        return -1;
    }
    int size, fd;
    void *mapped_memory = map_memory(argv[1], &size, &fd);
    pthread_t tids[2];
    pthread_create(tids, NULL, register_increaser, (void *) generate_data(mapped_memory, size));
    pthread_create(tids + 1, NULL, mark_decreaser, (void *) generate_data(mapped_memory, size));
    pthread_join(*tids, NULL);
    pthread_join(*(tids + 1), NULL);
}
