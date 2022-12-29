#include "interface.h"
#include <string.h>

struct thread_s{
  pthread_t *path;
  int index;
  int max_depth;
};

void *thread(void *parameter){
  void *return_value;
  int i = 0;
  pthread_t tids[2];
  thread_t t = *((thread_t *) parameter);
  t.path[t.index] = pthread_self();
  //fprintf(stdout, "%d %lu\n", t.index, pthread_self());
  if(t.index < t.max_depth - 1){
    pthread_create(tids, NULL, thread, generate_thread_structure(t.path, t.index + 1, t.max_depth));
    pthread_create(tids + 1, NULL, thread, generate_thread_structure(t.path, t.index + 1, t.max_depth));
    pthread_join(tids[0], &return_value);
    pthread_join(tids[1], &return_value);
  }else{
    char result[1000];
    char temp[1000];
    sprintf(result, "START -> %lu -> ", t.path[0]);
    for(i = 1;i < t.max_depth; i++){
      sprintf(temp, "%lu -> ", t.path[i]);
      strcat(result, temp);
    }
    strcat(result, "END");
    fprintf(stdout, "\n%s\n", result);
  }
  pthread_exit(0);
}

thread_t *generate_thread_structure(const pthread_t *path, int index, int max_depth){
  int i = 0;
  thread_t *t = (thread_t *) malloc(sizeof(thread_t));
  t->path = (pthread_t *) malloc(max_depth * sizeof(pthread_t));
  for(i < 0; i < index; i++)
    t->path[i] = path[i];
  t->index = index;
  t->max_depth = max_depth;
  return t;
}
