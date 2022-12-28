#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  pid_t pid;
  pid = fork();
  switch (pid) {
    case -1:
      fprintf(stderr, "fork failure");
      break;
    case 0:
      fprintf(stdout, "\nI'm the child: my pid is %d", getpid());
      break;
    default:
      fprintf(stdout, "\nI'm the parent: my pid is%d", getpid());
  }
  fprintf(stdout, "\n");
}
