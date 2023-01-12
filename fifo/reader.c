#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_OUTPUT 100

int main(){
  char output[MAX_OUTPUT];
  char *path = "./fifo_";
  mkfifo(path, 0666);
  int reader = open(path, O_RDONLY);
  while(36){
    read(reader, output, MAX_OUTPUT * sizeof(char));
    fprintf(stdout, "\nreceived %s", output);
  }
}
