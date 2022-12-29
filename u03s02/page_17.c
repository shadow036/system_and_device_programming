#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
  char str[10];
  int n = atoi(argv[1]) - 1;
  fprintf(stdout, "%d\n", n);
  if(n > 0){
    sprintf(str, "%d", n);
    execl(argv[0], argv[0], str, NULL);
  }
  fprintf(stdout, "End!\n");
  return 1;
}
