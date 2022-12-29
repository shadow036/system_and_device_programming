#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void manager(int sig){
  if(sig==SIGUSR1)
    fprintf(stdout, "received SIGUSR1");
  else if(sig == SIGUSR2)
    fprintf(stdout, "received SIGUSR2");
  else
    fprintf(stdout, "received %d", sig);
  return;
}

void sigChld(int signo){
  if(signo == SIGCHLD)
    fprintf(stdout, "received SIGCHLD");
  return;
}

int main(){
  signal(SIGUSR1, manager);
  signal(SIGUSR2, manager);
  signal(SIGCHLD, sigChld);
  kill(getpid(), SIGUSR1);
  if(fork() == 0)
    exit(0);
  else
    sleep(10);
}
