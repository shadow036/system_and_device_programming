#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void common_handler(int signo){
  return;
}

void child(){
  pid_t target = getppid();
  fprintf(stdout, "\nCHILD running pid: %d, ppid: %d", getpid(), target);
  while(1){
    sleep(5);
    kill(target, SIGUSR1);
    fprintf(stdout,"\nCHILD went asleep");
    pause();
    fprintf(stdout, "\nCHILD has been awakened");
  }
}

void parent(pid_t target){
  fprintf(stdout, "\nPARENT running pid: %d, child pid: %d", getpid(), target);
  while(1){
    fprintf(stdout,"\nPARENT went asleep");
    pause();
    fprintf(stdout, "\nPARENT has been awakened");
    sleep(5);
    kill(target, SIGUSR2);
  }
}

int main(){
  signal(SIGUSR1, common_handler);
  signal(SIGUSR2, common_handler);
  pid_t pid = fork();
  if(pid > 0)  // parent
    parent(pid);
  else
    child();
}
