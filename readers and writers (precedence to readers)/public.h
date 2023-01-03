#include <stdlib.h>
#include <pthread.h>

typedef struct data_reader_s data_reader_t;
typedef struct data_writer_s data_writer_t;

void *reader(void *);
void *writer(void *);
data_reader_t *generate_reader_structure(int *, data_writer_t *);
data_writer_t *generate_writer_structure();
