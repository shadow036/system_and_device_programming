#include "public.h"
#include <unistd.h>

int main(int argc, char **argv){
    if(argc != 3){
        write(STDOUT_FILENO, "wrong number of parameters", sizeof("wrong number of parameters"));
        return -1;
    }
    int number_of_readers = atoi(argv[1]);
    int number_of_writers = atoi(argv[2]);
    int active_readers = 0;
    data_writer_t *w = generate_writer_structure();
    data_reader_t *r = generate_reader_structure(&active_readers, w);
    pthread_t *tids = (pthread_t *) malloc((number_of_readers + number_of_writers) * sizeof(pthread_t));
    for(int i = 0; i < (number_of_readers + number_of_writers); i++){
        if(i < number_of_readers)
            pthread_create(tids + i, NULL, reader, (void *) r);
        else
            pthread_create(tids + i, NULL, writer, (void *) w);
    }
    for(int i = 0; i < (number_of_readers + number_of_writers); i++)
        pthread_join(tids[i], NULL);
}
