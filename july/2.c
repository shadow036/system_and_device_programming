#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include "header.h"

void *t1(void *);

int i;
pthread_t thread;

int main2(int p){
    i = p;
    if(fork())
        pthread_create(&thread, NULL, t1, (void *) &i);
    sleep(1);
    fprintf(stdout, "%d ", -i);
    return 0;
}
void *t1(void *a){
    i = *((int *) a);
    pthread_detach(pthread_self());
    fprintf(stdout, "%d ", i);
    i--;
    if(i > 0)
        pthread_create(&thread, NULL, t1, (void *) &i);
    return NULL;
}
