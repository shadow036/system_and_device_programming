#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct reader_s reader_t;
typedef struct writer_s writer_t;

reader_t *generate_reader_structure(int *);
writer_t *generate_writer_structure(int *, reader_t *);
void *reader(void *);
void *writer(void *);
