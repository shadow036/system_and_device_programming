/*
Write a C program that is able to handle signals as described by the following
specifications.
The program accepts signals SIGUSR1 and SIGUSR2, and:
- It displays a "success" message every time it receives a signal SIGUSR1 followed
  by a signal SIGUSR2, or vice-versa.
- It displays an error message every time it receives two signals SIGUSR1 or two
  signals SIGUSR2 consecutively.
- It terminates if it receives three successive SIGUSR1 or SIGUSR2 signals.

Suggestion
-----------
Once it is compiled, run the program in the background (...&) and use the shell
command "kill" to send signals SIGUSR1 and SIGUSR2 to the process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define bool int
#define true 1
#define false 0

bool flag = true;
int sequence[2];

void initialize_sequence(){
  sequence[0] = 0;
  sequence[1] = 0;
}

bool check_conditions(int current_signal){
  if(current_signal != sequence[1] && sequence[1] != 0){
    fprintf(stdout, "\nsuccess\n");
    sequence[0] = sequence[1];
    sequence[1] = current_signal;
  }else if(current_signal == sequence[1] && sequence[1] == sequence[0] && sequence[1] != 0){
    fprintf(stdout, "\nterminating...\n");
    return false;
  }else if(current_signal == sequence[1] && sequence[1] != 0){
    fprintf(stdout, "\nerror\n");
    sequence[0] = sequence[1];
    sequence[1] = current_signal;
  }else
    sequence[1] = current_signal;
  return true;
}

void signal_manager(int signo){
  fprintf(stdout, "\nreceived SIGUSR%d\n", signo == SIGUSR1 ? 1 : 2);
  flag = check_conditions(signo);
  return;
}

int main(){
  initialize_sequence();
  signal(SIGUSR1, signal_manager);
  signal(SIGUSR2, signal_manager);
  while(flag);
  return 0;
}
