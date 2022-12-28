/*Write a C program that receives two integer values on the command line,
h and n, and it generates a process tree of height h and degree n.

For example, if h=2 and n=2:
- the main process creates two processes
- each one of these 2 processes creates other two processes
- each one of these 4 processes creates other two processes
at this point, 8 leaf processes run and the program must stop.

More in detail each node of the tree is a process.
The initial process generates n child jobs and ends.
The same thing must be done by all child processes, generating a
number of processes on the leaves of the tree equal to n^h.
Processes on the leaves must all display their own PID and end.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
  if(argc != 3){
    fprintf(stderr, "wrong number of parameters!");
    return -1;
  }
  int h = atoi(argv[1]);
  int n = atoi(argv[2]);
  for(int height = 0; height < h + 1; height++){
    for(int child = 0; child < n; child++){
      pid_t pid = fork();
      if(pid != 0){
        fprintf(stdout, "\nparent %d generated child %d\n", getpid(), pid);
        if(child == n - 1){
          fprintf(stdout, "\nprocess %d dies\n", getpid());
          return 0;
        }
      }else
        break;
    }
  }
  fprintf(stdout, "\n%d\n", getpid());
  return 0;
}
