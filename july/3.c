#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include "header.h"

#define N 100

typedef struct record_s record_t;

record_t *generate_new_record(int);
void print_records(record_t *);

struct record_s{
    int i;
    char s[N];
    float f;
    record_t *next;
};
int main3(char *filename){
    record_t *head = NULL;
    record_t *tail = NULL;
    int fd = open(filename, O_RDWR, S_IRUSR | S_IWUSR);
    record_t *n_r;
    while((n_r = generate_new_record(fd)) != NULL){
        if(n_r == NULL)
            break;
        if(head == NULL){
            head = n_r;
            tail = n_r;
        }else{
            tail->next = n_r;
            tail = n_r;
        }
    }
    close(fd);
    print_records(head);
    return 0;
}

record_t *generate_new_record(int fd){
    int element = 0;
    int index = 0;
    char previous = 'A';
    void *buffer = (void *) malloc(sizeof(char));
    char int_[N];
    char float_[N];
    char s[N];
    int flag;
    while((flag = read(fd, buffer, sizeof(char))) > 0){
        char current = *((char *) buffer);
        if(current == '\n')
            break;
        else if(current != ' ' && current != '\n'){
            if(element == 0)
                int_[index++] = current;
            else if(element == 1)
                s[index++] = current;
            else
                float_[index++] = current;
            previous = current;
        }else if(previous != ' ' && current == ' '){
            if(element == 0)
                int_[index] = '\0';
            else if(element == 1)
                s[index] = '\0';
            else
                float_[index] = '\0';
            element++;
            index = 0;
        }
    }
    if(flag > 0){
        record_t *r = (record_t *) malloc(sizeof(record_t));
        r->i = atoi(int_);
        r->f = atof(float_);
        strcpy(r->s, s);
        r->next = NULL;
        return r;
    }else
        return NULL;
}
void print_records(record_t *records){
    for(record_t *c = records; c != NULL; c = c->next)
        fprintf(stdout, "\nint: %d\nstring: %s\nfloat: %.2f\n", c->i, c->s, c->f);
}
