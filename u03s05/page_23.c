#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CF 0
#define E 1
#define MAX_SLEEP 5

typedef struct t_s t_t;

struct t_s{
  char *instructions;
  int size;
};

int wait_random_time(int max){
  return rand() % max;
}

void *runner(void *par){
  t_t *original_struct = (t_t *) par;
  for(int i = 0; i < original_struct->size; i++){
    sleep(wait_random_time(MAX_SLEEP));
    fprintf(stdout, "\n%c", original_struct->instructions[i]);
  }
  pthread_exit(0);
}

int main(){
  long int t;
  srand((unsigned) time(&t));
  void *return_value;
  pthread_t tid_cf, tid_eg;
  t_t threads[2];
  pthread_t tids[2];
  fprintf(stdout, "A");
  threads[CF].size = 2;
  threads[CF].instructions = (char *) malloc(threads[CF].size * sizeof(char));
  threads[CF].instructions[0] = 'C';
  threads[CF].instructions[1] = 'F';
  pthread_create(&tids[CF], NULL, runner, (void *) threads + CF);
  fprintf(stdout, "\nB");
  threads[E].size = 1;
  threads[E].instructions = (char *) malloc(threads[E].size * sizeof(char));
  threads[E].instructions[0] = 'E';
  pthread_create(&tids[E], NULL, runner, (void *) (threads + E));
  fprintf(stdout, "\nD");
  pthread_join(tids[E], &return_value);
  pthread_join(tids[CF], &return_value);
  fprintf(stdout, "\nG\n");
  return 0;
}
