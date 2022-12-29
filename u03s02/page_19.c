#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
  int n = 0;
  while(n < 3 && fork()){
    if(!fork())
      execlp("echo", "n++", "n", NULL);
    n++;
    fprintf(stdout,"%d\n", n);
  }
  return 1;
}
