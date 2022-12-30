/*
File stores *binary* information with *fixed-length* records
using the format of file_2 of Exercise 01.
Write a program to implement a user menu with the following options:

- R n: Where R is the character 'R', and n is an integer value.
       Read from file the record representing student number n and
       display this information on standard output.

- W n: Where W is the character 'W', and n is an integer value.
       Read from standard input all data fields for the student number
       n and write them on the file in position n.

- E: End the program.

The input file name is given on the command line.

The following is an example of execution (using the file presented in
Exercise 01):

> R 3     // Read info for student 3
3 200000 Verdi Giacomo 15
> R 1     // Read info for student 1
1 100000 Romano Antonio 25
> W 1     // Over-write info for student 1
          // with info read from standard input
          // Read input data
Data: 1 100000 Romano Antonio 27
          // Overwrite record on file ...
> W 5     // Add info for student in position 5
          // with info read from standard input
          // Read input data
Data: 5 157143 White House 30
          // Overwrite record on file ...
> E       // End program

where
- "//" specifies explanatory comments not program I/O lines
- "R 3", "R 1", "W 1", etc. are the user inputs
- all other characters belong to the program output.

Future development
Once file locking has been introduced
--------------------------------------
Lock each record before reading (or writing) it, and release the
same record as soon as the operation has been performed.
(Notice that locking, for now at least, is useless, but it will be useful
with multi-threaded applications).
*/
#include "2.h"

int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr, "wrong number of parameters");
    return -1;
  }
  menu(argv[1]);
  return 0;
}
