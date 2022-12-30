#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 30 + 1

void **open_files(char *, char *, char*);
void text_to_binary(FILE *, int);
void binary_to_text(int, FILE *);
void close_files(void **);
