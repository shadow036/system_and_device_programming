#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include "header.h"

void print_files(char *, char *, char *);

int main4(char *file1, char *file2, char *file3){
    int f1 = open(file1, O_RDWR, 0);
    int f2 = open(file2, O_RDWR, 0);
    int f3 = open(file3, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR);
    int n1, n2;
    read(f1, (void *) &n1, sizeof(int));
    read(f2, (void *) &n2, sizeof(int));
    int n3 = n1 + n2;
    write(f3, (void *) &n3, sizeof(int));
    void *f1_mapped = mmap(0, sizeof(int) + n1 * sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED, f1, 0);
    void *f2_mapped = mmap(0, sizeof(int) + n2 * sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED, f2, 0);
    void *f3_mapped = mmap(0, sizeof(int) + (n1 + n2) * sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED, f3, 0);
    float *f1_current = (float *) (f1_mapped + sizeof(int) + (n1 - 1) * sizeof(float));
    float *f2_current = (float *) (f2_mapped + sizeof(int) + (n2 - 1) * sizeof(float));
    float *f3_current = (float *) (f3_mapped + sizeof(int));
    while(f1_current >= f1_mapped + sizeof(int) || f2_current >= f2_mapped + sizeof(int)){
        if(*f1_current > *f2_current || f2_current < f2_mapped + sizeof(int)){
            *f3_current = *f1_current;
            f3_current++;
            f1_current--;
        }else{
            *f3_current = *f2_current;
            f3_current++;
            f2_current--;
        }
    }
    close(f1);
    close(f2);
    close(f3);
    munmap(f1_mapped, sizeof(int) + n1 * sizeof(float));
    munmap(f2_mapped, sizeof(int) + n2 * sizeof(float));
    munmap(f3_mapped, sizeof(int) + (n1 + n2) * sizeof(float));
    print_files(file1, file2, file3);
    return 0;
}

void print_files(char *file1, char *file2, char *file3){
    int f1 = open(file1, O_RDONLY, 0);
    int f2 = open(file2, O_RDONLY, 0);
    int f3 = open(file3, O_RDONLY, 0);
    int n;
    float v;
    read(f1, &n, sizeof(int));
    printf("\n%d ", n);
    //write(STDOUT_FILENO, &n, sizeof(int));
    while(read(f1, &v, sizeof(float)) > 0)
        printf("%f ", v);

    read(f2, &n, sizeof(int));
    printf("\n%d ", n);
    while(read(f2, &v, sizeof(float)) > 0)
        printf("%f ", v);
    //write(STDOUT_FILENO, &n, sizeof(int));

    read(f3, &n, sizeof(int));
    printf("\n%d ", n);
    while(read(f3, &v, sizeof(float)) > 0)
        printf("%f ", v);
    //write(STDOUT_FILENO, &n, sizeof(int));
}