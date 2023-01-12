#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

int main(int argc, char **argv){
    int ex = atoi(argv[1]);
    switch(ex){
        case 1:
            return main1(atoi(argv[2]), argv[0]);
        case 3:
            return main3(atoi(argv[2]));
        default:
            return -1;
    }
}