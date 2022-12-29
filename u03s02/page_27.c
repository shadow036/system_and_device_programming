#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
  int n = atoi(argv[1]);
  char str[10];
  if(n > 0){
    fprintf(stdout, "%d\n", n);
    sprintf(str, "%s %d", argv[0], n - 1);
    system(str);
  }
  fprintf(stdout,"end\n");
  return 1;
}
