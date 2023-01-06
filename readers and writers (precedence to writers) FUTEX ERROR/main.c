#include "public.h"

int main(int argc, char **argv){
    if(argc != 3){  // filename, # readers, # writers
        write(STDOUT_FILENO, "wrong number of parameters", sizeof("wrong number of parameters"));
        return -1;
    }
    int number_of_readers = atoi(argv[1]);
    int number_of_writers = atoi(argv[2]);
    int active_readers, active_writers = 0;
    int i;
    reader_t *r = generate_reader_structure(&active_readers);
    writer_t *w = generate_writer_structure(&active_writers, r);
    pthread_t *tids = (pthread_t *) malloc((number_of_readers + number_of_writers) * sizeof(pthread_t));
    for(i = 0; i < (number_of_readers + number_of_writers); i++){
        if(i < number_of_readers)
            pthread_create(tids + i, NULL, reader, (void *) r);
        else
            pthread_create(tids + i, NULL, writer, (void *) w);
    }
    for(i = 0; i < (number_of_readers + number_of_writers); i++)
        pthread_join(*(tids + i), NULL);
}
