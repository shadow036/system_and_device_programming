#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  if(argc != 3)
    fprintf(stdout, "wrong number of parameters!");
  int sleep_parent = atoi(argv[1]);
  int sleep_child = atoi(argv[2]);
  pid_t pid = fork();
  switch(pid){
    case -1:
      fprintf(stderr, "fork error");
      break;
    case 0:
      sleep(sleep_child);
      fprintf(stdout, "im the child, pid: %d, ppid: %d", getpid(), getppid());
      break;
    default:
      sleep(sleep_parent);
      fprintf(stdout, "im the parent, pid: %d, ppid: %d", getpid(), getppid());
      break;
  }
  return 0;
}
