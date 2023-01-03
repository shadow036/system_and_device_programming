/*A parent process P generates two children processes C1 and C2.
C1 and P communicate through a pipe p1 and C2 and P communicate
through a pipe p2.
- Process C1:
  every WAIT_TIME_1 seconds generates a string of STR_SIZE small alphabetic
  letters at most (i.e., from 1 to STR_SIZE letters) and writes the string
  into pipe p1.
  Overall C1 generates and writes on pipe p1, STR_NUM strings of variable length.
- Process C2:
  does the same things done by C1 but it waits for WAIT_TIME_2
  seconds, and it writes the strings into pipe p2.
- Process P:
  reads the strings coming from the two pipes (p1 and p2), converts
  them in capital letters, and displays them on standard output.

Note that:
- WAIT_TIME_1, WAIT_TIME_2, STR_NUM, and STR_SIZE are predefined
  constant values.
- Strings are randomly generated (composed by only small alphabetic
  letters) of variable length.

Write 4 versions of the program:

A. Using blocking I/O system calls.
B. Using non-blocking I/O system calls.
C. Using multiplexing I/O.
D. Using asynchronous I/O.

Analyze and compare the outputs generated by the different versions of
the program.

Suggestion
----------

Processes C1 and C2 write strings of variable *length* on pipes p1 and
p2, respectively.
To let the parent process P to read these strings "synchronously", it is
better to use the following simple communication protocol:
- C1 and C2, before writing the string onto the pipe, write its length,
  i.e., a single integer value.
- P reads the integer value n and then it reads exactly n characters
  (thus it synchronizes its reading operation with the writing operation
  on the other end of the pipe).
The alternative would be to read from the pipe character-by-character
until finding the termination character of each string ('\0').*/

#include "1a.h"
#include <unistd.h>
#include <time.h>

int generate_length();
char *generate_string(int);

int **generate_and_activate_pipes(){
    int **pipes = (int **) malloc(2 * sizeof(int *));
    for(int i = 0; i < 2; i++)
        pipes[i] = (int *) malloc(sizeof(int));
    pipe(pipes[0]);
    pipe(pipes[1]);
    return pipes;
}

int generate_length(){
    srand(time(0));
    int l = 1 + (rand() % STR_SIZE);
    return l;
}

char *generate_string(int l){
    char *message = (char *) malloc(l * sizeof(char));
    for(int i = 0; i < l; i++)
        message[i] = (char) (97 + (rand() % 26));
    return message;
}

void C(int *pipe, int wait_time){
    close(pipe[0]); // close the reading end
    int counter = 0;
    while(counter < STR_NUM){
        sleep(wait_time);
        int l = generate_length();
        write(pipe[1], (void *) &l, sizeof(int));
        fprintf(stdout, "\nC%d -[%d]-> {%d}\n", wait_time == WAIT_TIME_1 ? 1 : 2, pipe[1], l);
        //fprintf(stdout, "\nC%d -> {%d}\n", wait_time == WAIT_TIME_1 ? 1 : 2, l);
        char *message = generate_string(l);
        write(pipe[1], (void *) message, l);
        fprintf(stdout, "\nC%d -[%d]-> {%s}\n", wait_time == WAIT_TIME_1 ? 1 : 2, pipe[1], message);
        //fprintf(stdout, "\nC%d -> {%s}\n", wait_time == WAIT_TIME_1 ? 1 : 2, message);
        counter++;
    }
}

void P(int *pipe1, int *pipe2){
    fprintf(stdout, "\nP process started...\n");
    int counter = 0;
    close(pipe1[1]); // close the writing end
    close(pipe2[1]); // close the writing end
    int l1, l2;
    char *message1;
    char *message2;
    while(counter < STR_NUM){
        read(pipe1[0], &l1, sizeof(int));   // get size message C1
        fprintf(stdout, "\n{%d} <-[%d]- C1\n", l1, pipe1[0]);
        //fprintf(stdout, "\n{%d} <- C1\n", l1);

        message1 = (char *) malloc(l1 * sizeof(char));

        read(pipe1[0], message1, l1 * sizeof(char));    // get message C1
        fprintf(stdout, "\n{%s} <-[%d]- C1\n", message1, pipe1[0]);
        //fprintf(stdout, "\n{%s} <- C1\n", message1);


        read(pipe2[0], &l2, sizeof(int));   // get size message C2
        fprintf(stdout, "\n{%d} <-[%d]- C2\n", l2, pipe2[0]);
        //fprintf(stdout, "\n{%d} <- C2\n", l2);

        message2 = (char *) malloc(l2 * sizeof(char));

        read(pipe2[0], message2, l2 * sizeof(char));    // get message C2
        fprintf(stdout, "\n{%s} <-[%d]- C2\n", message2, pipe2[0]);
        //fprintf(stdout, "\n{%s} <- C2\n", message2);

        counter++;
    }
}

void free_pipes(int **pipes){
    for(int i = 0; i < 2; i++)
        free(pipes[i]);
}
