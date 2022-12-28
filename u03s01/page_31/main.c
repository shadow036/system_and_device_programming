#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void s1();
void s2();
void s3();
void s4();
void s5();
void s6();

void s1(){
  fprintf(stdout, "s1");
}

void s2(){
  fprintf(stdout, " s2");
}

void s4(){
  fprintf(stdout, " s4");
}

void s3(){
  fprintf(stdout, " s3");
  int stat_loc;
  pid_t pid = fork();
  switch (pid) {
    case -1:
      fprintf(stderr, "fork error");
      break;
    case 0:
      s6();
      break;
    default:
      s5();
      wait(&stat_loc);
      break;
  }
}

void s5(){
  fprintf(stdout, " s5");
}

void s6(){
  fprintf(stdout, " s6");
}

void s7(){
  fprintf(stdout, " s7");
}

int main(){
  pid_t pid = fork();
  int stat_loc;
  switch (pid) {
    case -1:
      fprintf(stderr, "fork error");
      break;
    case 0: // s3
      s3();
      break;
    default:  //parent
      s2();
      s4();
      wait(&stat_loc);
      s7();
      break;
  }
  return 0;
}
