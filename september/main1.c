#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

#define N 100

int main1(int n, char *argv_0){
    char str[N];
    setbuf(stdout, 0);
    if(n > 0 && !fork()){
        if(!fork()){
            fprintf(stdout, "E");
            sprintf(str, "%d", n - 1);
            execlp(argv_0, argv_0, str, NULL);
        }else{
            sprintf(str, "echo -n S");
            system(str);
        }
    }
    return 1;
}