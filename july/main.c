#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

#include "header.h"

int main(int argc, char **argv){
    int ex = atoi(argv[1]);
    switch(ex){
        case 1:
            return main1(atoi(argv[2]), argv[0]);
        case 2:
            return main2(atoi(argv[2]));
        case 3:
            return main3(argv[2]);
        case 4:
            return main4(argv[2], argv[3], argv[4]);
        default:
            return -1;
    }
}