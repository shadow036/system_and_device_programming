/*
Exercise 3 (2.0 points)
A program can execute four different threads, namely TP (thread plus), TM (thread minus), TS (thread
star), and TNL (thread newline). Each thread is organized through an infinite cycle containing
synchronization instructions but a single I/O instruction:
- Thread TP includes instruction printf ("+")
- Thread TM includes instruction printf ("-")
- Thread TS includes instruction printf ("*")
- Thread TNL includes instruction printf ("\n").
Synchronize the four threads to print the following sequence of lines:
++++++++++
----------
**********
++++++++++
----------
**********
etc.where the number of characters on each row is equal to a constant value N (that is, 10 in the previous
example).
*/
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

sem_t sem_plus, sem_minus, sem_star, sem_newline;
int token = 0;

void *TP(void *);
void *TM(void *);
void *TS(void *);
void *TNL(void *);
void initialize_semaphores();

int main(int argc, char **argv){
    int n = atoi(argv[1]);
    initialize_semaphores();
    pthread_t tids[4];
    pthread_create(tids, NULL, TP, (void *) &n);
    pthread_create(tids + 1, NULL, TM, (void *) &n);
    pthread_create(tids + 2, NULL, TS, (void *) &n);
    pthread_create(tids + 3, NULL, TNL, (void *) &n);
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_join(tids[2], NULL);
    pthread_join(tids[3], NULL);
    return 0;
}

void *TP(void *p){
    while(36){
        sem_wait(&sem_plus);
        for(int i = 0; i < *((int *) p); i++)
            fprintf(stdout, "+");
        sem_post(&sem_newline);
    }
}

void *TM(void *p){
    while(36){
        sem_wait(&sem_minus);
        for(int i = 0; i < *((int *) p); i++)
            fprintf(stdout, "-");
        sem_post(&sem_newline);
    }
}

void *TS(void *p){
    while(36){
        sem_wait(&sem_star);
        for(int i = 0; i < *((int *) p); i++)
            fprintf(stdout, "*");
        sem_post(&sem_newline);
    }
}

void *TNL(void *p){
    while(36){
        sem_wait(&sem_newline);
        fprintf(stdout, "\n");
        token = (token + 1) % 3;
        if(token == 0)
            sem_post(&sem_plus);
        else if(token == 1)
            sem_post(&sem_minus);
        else if(token == 2)
            sem_post(&sem_star);
    }
}

void initialize_semaphores(){
    sem_init(&sem_plus, 0, 1);
    sem_init(&sem_minus, 0, 0);
    sem_init(&sem_star, 0, 0);
    sem_init(&sem_newline, 0, 0);
}