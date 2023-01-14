/*
Two processes P1 and P2 shared two memory buffers to optimize their effort using a pipeline approach in which
their tasks can be divided into two units of times in the following way.
In a first-time unit, P1 randomly generates floating-point numbers in the first buffer while P2 sorts (in ascending
order) the number stored in the second buffer. When both P1 and P2 have finished, they switch the buffers such
that P1 first displays the number sorted by P2 and then it randomly generates a new set of floating-point
numbers in the second buffer while P2 sorts (in ascending order) the number stored in the first buffer.
The size of the two buffers is supposed to be constant and the candidate must decide how to synchronize the
two processes at the end of each phase.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFER_SIZE 4

enum ends{READING_END, WRITING_END};

float *obtain_shared_memory(char *, int, int *);
void generate_random_numbers(float *);
void sort_numbers(float *);
void print_buffer(float *);

int main(int argc, char **argv){
    int id1, id2;
    float *buffer1 = obtain_shared_memory(argv[1], 0, &id1);
    float *buffer2 = obtain_shared_memory(argv[2], 1, &id2);
    buffer2[0] = 9.9;
    buffer2[1] = 3.3;
    buffer2[2] = 7.7;
    int pipe_buffer1[2];
    int pipe_buffer2[2];
    pipe(pipe_buffer1);
    pipe(pipe_buffer2);
    int done = 36;
    if(fork() > 0){
        close(pipe_buffer1[READING_END]);
        close(pipe_buffer2[WRITING_END]);

        printf("\n------------------------\nbuffer 2 - beginning\n");
        print_buffer(buffer2);
        printf("\n------------------------");
        generate_random_numbers(buffer1);
        printf("\n------------------------\nbuffer 1 - beginning\n");
        print_buffer(buffer1);
        printf("\n------------------------");
        write(pipe_buffer1[WRITING_END], (void *) &done, sizeof(int));
        read(pipe_buffer2[READING_END], (void *) &done, sizeof(int));

        printf("\n------------------------\nbuffer 2 - after sorting\n");
        print_buffer(buffer2);
        printf("\n------------------------");
        generate_random_numbers(buffer2);

        wait(NULL);
        shmdt(buffer1);
        shmdt(buffer2);
        shmctl(id1, IPC_RMID, NULL);
        shmctl(id2, IPC_RMID, NULL);
    }else{
        sleep(10);
        close(pipe_buffer1[WRITING_END]);
        close(pipe_buffer2[READING_END]);

        sort_numbers(buffer2);

        write(pipe_buffer2[WRITING_END], (void *) &done, sizeof(int));
        read(pipe_buffer1[READING_END], (void *) &done, sizeof(int));

        sort_numbers(buffer1);
        printf("\n------------------------\nbuffer 1 - after sorting\n");
        print_buffer(buffer1);
        printf("\n------------------------");
    }
    return 0;
}

float *obtain_shared_memory(char *filename, int v, int *id){
    key_t key = ftok(filename, v);
    *id = shmget(key, BUFFER_SIZE, 0666 | IPC_CREAT);
    return ((float *) shmat(*id, NULL, 0));
}

void generate_random_numbers(float *buffer){
    srand(time(0));
    for(int i = 0; i < BUFFER_SIZE; i++){
        buffer[i] = (rand() % 10) / 11.0;
        fprintf(stdout, "\n[%d] - written %.1f at location %p\n", getpid(), buffer[i], buffer + i);
        sleep(rand() % 6);
    }
}
void sort_numbers(float *buffer){
    float temporary;
    //for(float *buffer1 = buffer; buffer1 < (float *) ((char *) buffer + BUFFER_SIZE); buffer1++){
    //    for(float *buffer2 = buffer; buffer2 < (float *) ((char *) buffer + BUFFER_SIZE); buffer2++){
    for(int i = 0; i < BUFFER_SIZE; i++){
        for(int j = 0; j < BUFFER_SIZE; j++){
            if(buffer[i] > buffer[j]){
                temporary = buffer[j];
                buffer[j] = buffer[i];
                buffer[i] = temporary;
            }
        }
    }
}

void print_buffer(float *buffer){
    for(int i = 0; i < BUFFER_SIZE; i++)
        fprintf(stdout, "\n[%d] - %p: %.1f\n", getpid(), buffer + i, buffer[i]);
}