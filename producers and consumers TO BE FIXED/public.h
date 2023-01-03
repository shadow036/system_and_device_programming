#include <stdlib.h>
#include <unistd.h>

typedef struct data_s data_t;

void *producer(void *);
void *consumer(void *);
data_t *generate_thread_parameters(char *, int, int *, int *, int *, int *);
