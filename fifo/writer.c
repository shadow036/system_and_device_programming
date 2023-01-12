#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define bool int
#define true 1
#define false 0
#define MAX_INPUT 100

int main(){
  bool flag = true;
  char input[MAX_INPUT];
  char *path = "./fifo_";
  mkfifo(path, 0666);
  int writer = open(path, O_WRONLY);
  while(flag){
    read(STDIN_FILENO, input, MAX_INPUT * sizeof(char));
    if(!strcmp(input, "end\n"))
      flag = false;
    else
      write(writer, input, strlen(input));
  }
  close(writer);
}
