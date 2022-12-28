#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define TRANSFORM 1
#define DISPLAY 2

#define START_TRANSFORM 1
#define START_DISPLAY 2
#define END_READ 3
#define END_TRANSFORM 3
#define END 4

#define True 1
#define False 0

#define bool int

int flag = 0;
char read_registers[3];
char transform_registers[2];
int offsets[3][2];
