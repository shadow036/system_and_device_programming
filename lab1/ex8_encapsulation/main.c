/*
Code implementation with threads
--------------------------------

In linear algebra, the multiplication of matrices is the operation that
produces a new matrix C by making the product rows for columns of two
given matrices A and B.
More in detail, if A has size [r, x] and B has size [x, c], then C will
have size [r, c], and each of its own position elements (i, j) will be
computed as:

C[i][j] = \sum_{k=0}^{x-1} A[i][k] x B[k][j]

Write a multithreaded function

void mat_mul (int **A, int **B, int r, int x, int c, int **C);

able to generate the matrix C, running a thread to compute
each one of its elements.
Each thread will calculate the value of the element, making the product
rows by columns previously specified.
Properly define the data structure required to run the threads.

*/
#include "interface.h"

int main(int argc, char **argv){
  pthread_t *tids;
  void *return_value;
  int i, j = 0;
  if(argc != 2){
    fprintf(stderr, "wrong number of parameters");
    return -1;
  }
  FILE *f = fopen(argv[1], "r");
  matrices_t *m = load_matrices(f);
  if(error_flag_getter(m) == true)
    return -1;
  display_matrices(m);
  tids = (pthread_t *) malloc(A_r_getter(m) * B_c_getter(m) * sizeof(pthread_t));
  for(i = 0; i < A_r_getter(m); i++){
    for(j = 0; j < B_c_getter(m); j++)
      pthread_create(&tids[i + B_c_getter(m) * j], NULL, thread,
      (void *) generate_thread_structure(A_getter(m), B_getter(m), A_c_getter(m),
        i, j, R_getter(m)));
  }
  for(i = 0; i < A_r_getter(m); i++){
    for(j = 0; j < B_c_getter(m); j++)
      pthread_join(tids[i + B_c_getter(m)], &return_value);
  }
  display_matrices(m);
}
