#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr, "wrong number of parameters");
    return -1;
  }
  int n = atoi(argv[1]);
  int i = 0;
  int stat_loc;
  int *array = (int *) malloc(n * sizeof(int));
  for(i = 0; i < n; i++)
    fscanf(stdin, "%d", array+i);
  for(i = 0; i < n - 1; i++){
    pid_t pid = fork();
    if(pid != 0){
      wait(&stat_loc);
      fprintf(stdout,"%d ", array[i]);
      return 0;
    }
  }
  fprintf(stdout,"%d ", array[n - 1]);
  return 0;
}
