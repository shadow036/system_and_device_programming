#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include "header.h"

typedef struct record_s record_t;

int main1(int n, char *argv_0){
    char str[50];
    setbuf(stdout, 0);
    if(n > 0){
        if(fork() > 0){
            if(fork() > 0){
                if(fork() > 0){
                    sprintf(str, "%s %d %d", argv_0, 1, n - 1);
                    system(str);
                }else{
                    system("echo -n 1");
                }
            }else{
                system("echo -n 2");
            }
        }else{
            system("echo -n 3");
        }
    }
    return 0;
}
