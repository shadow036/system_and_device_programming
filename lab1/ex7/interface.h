#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct thread_s thread_t;

void *thread(void *);
thread_t *generate_thread_structure(const pthread_t *, int, int);
