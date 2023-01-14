/*
A process P orchestrates the following operations:
It receives real values from two different FIFOs. The first FIFO connects P with P1, and the
second connects P with P2. P1 and P2 send real values to P with different rates.
It uses I/O multiplexing to read the data from the two FIFOs.
It stores all real values it receives in a memory-mapped file. The process P terminates when it
receives a value equal to zero from both P1 and P2 (even if the two zeros are not contiguous).
Implement the process P in C language, whereas the implementation of P1 and P2 is not required.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define is ==

typedef struct timeval timeval;
typedef enum bool bool;
enum bool{false, true};
enum pid{P1_, P2_};
void P(char *, char *, pid_t *, char *);
void P1(char *);
void P2(char *);

int main(int argc, char **argv){
    pid_t children_pids[2];
    if((children_pids[P1_] = fork()) > 0){
        if((children_pids[P2_] = fork()) > 0)
            P(argv[1], argv[2], children_pids, argv[3]);
        else
            P2(argv[2]);
    }else
        P1(argv[1]);
}

void P(char *fifo_filename1, char *fifo_filename2, pid_t *children_pids, char *memory_mapped_file){
    int descriptor3 = open(memory_mapped_file, O_RDWR | O_CREAT);
    float *starting_address = (float *) mmap(0, 1000 * sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED, descriptor3, 0);
    float *slider = starting_address;
    bool flags[2];
    flags[P1_] = flags[P2_] = false;
    mkfifo(fifo_filename1, 0666);
    int descriptor1 = open(fifo_filename1, O_RDONLY | O_CREAT);
    mkfifo(fifo_filename2, 0666);
    int descriptor2 = open(fifo_filename2, O_RDONLY | O_CREAT);
    fd_set reading_set;
    FD_ZERO(&reading_set);
    FD_SET(descriptor1, &reading_set);
    FD_SET(descriptor2, &reading_set);
    timeval t;
    t.tv_sec = 1;
    t.tv_usec = 0;
    float value;
    int max_pid = children_pids[P1_] > children_pids[P2_] ? children_pids[P1_] : children_pids[P2_];
    while(flags[P1_] is false || flags[P2_] is false){
        select(max_pid + 1, &reading_set, NULL, NULL, &t);
        if(FD_ISSET(descriptor1, &reading_set)){
            read(descriptor1, (void *) &value, sizeof(float));
            fprintf(stdout, "\nP receives %.1f from P1\n", value);
            *slider = value;
            slider++;
            fprintf(stdout, "\nP writes %.1f into %s\n", value, memory_mapped_file);
            if(value == 0){
                flags[P1_] = true;
                if(flags[P2_] is true){
                    kill(children_pids[P1_], SIGKILL);
                    kill(children_pids[P2_], SIGKILL);
                    return;
                }
            }
        }
        if(FD_ISSET(descriptor2, &reading_set)){
            read(descriptor2, (void *) &value, sizeof(float));
            fprintf(stdout, "\nP receives %.1f from P2\n", value);
            *slider = value;
            slider++;
            fprintf(stdout, "\nP writes %.1f into %s\n", value, memory_mapped_file);
            if(value == 0){
                flags[P2_] = true;
                if(flags[P1_] is true){
                    kill(children_pids[P1_], SIGKILL);
                    kill(children_pids[P2_], SIGKILL);
                    return;
                }
            }
        }
    }
}

void P1(char *fifo_filename){
    srand(time(0));
    mkfifo(fifo_filename, 0666);
    int descriptor = open(fifo_filename, O_WRONLY | O_CREAT);
    float value;
    while(36){
        sleep(rand() % 3);
        value = (rand() % 11) / 10.0;
        fprintf(stdout, "\nP1 sends %.1f\n", value);
        write(descriptor, (void *) &value, sizeof(float));
    };
}

void P2(char *fifo_filename){
    srand(time(0));
    mkfifo(fifo_filename, 0666);
    int descriptor = open(fifo_filename, O_WRONLY | O_CREAT);
    float value;
    while(36){
        sleep(rand() % 3);
        value = (rand() % 11) / 10.0;
        fprintf(stdout, "\nP2 sends %.1f\n", value);
        write(descriptor, (void *) &value, sizeof(float));
    };
}