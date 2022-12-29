#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define bool int
#define true 1
#define false 0

typedef struct matrices_s matrices_t;
typedef struct thread_structure_s thread_structure_t;

thread_structure_t *generate_thread_structure(int **, int **, int, int, int, int **);
void *thread(void *);
int error_flag_getter(matrices_t *);
int A_r_getter(matrices_t *);
int A_c_getter(matrices_t *);
int B_c_getter(matrices_t *);
int **A_getter(matrices_t *);
int **B_getter(matrices_t *);
int **R_getter(matrices_t *);
matrices_t *load_matrices(FILE *);
void display_matrices(matrices_t *);

#endif
