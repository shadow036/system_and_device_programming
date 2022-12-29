#include "interface.h"

struct matrices_s{
  int **A;
  int **B;
  int **R;
  int A_r;
  int A_c;
  int B_r;
  int B_c;
  bool error_flag;
};

struct thread_structure_s{
  int **A;
  int **B;
  int elements;
  int x;
  int y;
  int **R;
};

void *thread(void *str){
  int i = 0;
  thread_structure_t t = *((thread_structure_t *) str);
  for(i = 0; i < t.elements; i++)
    t.R[t.x][t.y] += (t.A[t.x][i] * t.B[i][t.y]);
  pthread_exit(0);
}

int error_flag_getter(matrices_t *m){
  return m->error_flag;
}

int A_r_getter(matrices_t *m){
  return m->A_r;
}

int A_c_getter(matrices_t *m){
  return m->A_c;
}

int B_c_getter(matrices_t *m){
  return m->B_c;
}

int **A_getter(matrices_t *m){
  return m->A;
}

int **B_getter(matrices_t *m){
  return m->B;
}

int **R_getter(matrices_t *m){
  return m->R;
}

thread_structure_t *generate_thread_structure(
  int **A,
  int **B,
  int elements,
  int x,
  int y,
  int **R){
    thread_structure_t *t = (thread_structure_t *) malloc(sizeof(thread_structure_t));
    t->A = A;
    t->B = B;
    t->elements = elements;
    t->x = x;
    t->y = y;
    t->R = R;
    return t;
}

matrices_t *load_matrices(FILE *f){
  matrices_t *m = (matrices_t *) malloc(sizeof(matrices_t));
  int r, x1, x2, c;
  int i, j, i2, j2, k, k2 = 0;
  fscanf(f, "%d %d %d %d", &r, &x1, &x2, &c);
  if(x1 != x2){
    m->error_flag = true;
    fprintf(stdout, "matrices are not compatible, terminating...");
    return m;
  }
  m->A_r = r;
  m->A_c = x1;
  m->B_r = x2;
  m->B_c = c;
  m->error_flag = false;
  m->A = (int **) malloc(r * sizeof(int *));
  m->B = (int **) malloc(x2 * sizeof(int *));
  m->R = (int **) malloc(r * sizeof(int *));
  for(i = 0; i < r; i++){
    m->A[i] = (int *) malloc(x1 * sizeof(int));
    for(i2 = 0; i2 < x1; i2++)
      fscanf(f, "%d", &(m->A[i][i2]));
  }
  for(j = 0; j < x2; j++){
    m->B[j] = (int *) malloc(c * sizeof(int));
    for(j2 = 0; j2 < c; j2++)
      fscanf(f, "%d", &(m->B[j][j2]));
  }
  for(k = 0; k < r; k++){
    m->R[k] = (int *) malloc(c * sizeof(int));
    for(k2 = 0; k2 < c; k2++)
      m->R[k][k2] = 0;
  }
  return m;
}

void display_matrices(matrices_t *m){
  fprintf(stdout,"matrix A: (%dx%d)\n", m->A_r, m->A_c);
  int i, j = 0;
  for(i = 0; i < m->A_r; i++){
    for(j = 0; j < m->A_c; j++)
      fprintf(stdout, "%d ", m->A[i][j]);
    fprintf(stdout, "\n");
  }
  fprintf(stdout,"\nmatrix B: (%dx%d)\n", m->B_r, m->B_c);
  for(i = 0; i < m->B_r; i++){
    for(j = 0; j < m->B_c; j++)
      fprintf(stdout, "%d ", m->B[i][j]);
    fprintf(stdout, "\n");
  }
  fprintf(stdout,"\nresult matrix: (%dx%d)\n", m->A_r, m->B_c);
  for(i = 0; i < m->A_r; i++){
    for(j = 0; j < m->B_c; j++)
      fprintf(stdout, "%d ", m->R[i][j]);
    fprintf(stdout, "\n");
  }
  fprintf(stdout, "\nerror flag: %d\n---------------------\n", m->error_flag);
}
