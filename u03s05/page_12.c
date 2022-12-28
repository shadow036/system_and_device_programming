#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define N_THREADS 5
#define N 10

typedef struct structure_s structure_t;

struct structure_s{
  int id;
};

void *thread_runner(void *par){
  structure_t parameter = *((structure_t *) par);
  fprintf(stdout, "\nthread %d", parameter.id);
  pthread_exit(NULL);
}

void *wrong_thread_runner(void *par){
  int parameter = *((int *) par);
  fprintf(stdout, "\nthread %d", parameter);
  pthread_exit(NULL);
}

int main(){
  structure_t threads[N_THREADS];
  pthread_t ids[N_THREADS];
  for(int i=0;i<N_THREADS;i++){
    threads[i].id = i;
    pthread_create(ids + i, NULL, &thread_runner, (void *) (threads + i));
    //pthread_create(ids + i, NULL, &wrong_thread_runner, (void *) &i);
  }
  void *valuePtr;
  for(int i=0;i<N_THREADS;i++)
    pthread_join(ids[i], &valuePtr);
  return 0;
}
