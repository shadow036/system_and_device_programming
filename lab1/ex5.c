/*
A binary number of size n can be easily generated by a recursive function
like the one reported in file e05recursive.c

Transform the recursive program into a concurrent one, replacing the
recursive procedure with the generation of an appropriate number of
*processes*.
Each process must display one binary number.
Binary numbers can be displayed in any order.

For example, if n=3, the function must generate and print numbers:
000, 001, 010, 011, 100, 101, 110, 111
IN ANY ORDER.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stdout, "wrong number of parameters!");
    return -1;
  }
  int n = atoi(argv[1]);
  int i, j = 0;
  pid_t pid = 0;
  char *binary_number = (char *) malloc(n * sizeof(char));
  for(i = 0; i < n; i++){
      pid = fork();
      if(pid > 0)
        binary_number[n - 1 - i] = '0';
      else
        binary_number[n - 1 - i] = '1';
  }
  fprintf(stdout, "\n%s\n", binary_number);
  return 0;
}