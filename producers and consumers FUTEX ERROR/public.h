#include <stdlib.h>
#include <unistd.h>

typedef struct data_s data_t;

void *producers(void *);
void *consumers(void *);
data_t *generate_thread_parameters(char *, int, int *, int *);
