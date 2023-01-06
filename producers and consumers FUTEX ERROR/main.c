#include "public.h"
#include <pthread.h>

int main(int argc, char **argv){
    if(argc != 4){
        write(STDOUT_FILENO, "wrong number of parameters", sizeof("wrong number of parameters"));
        return -1;
    }
    int i;
    int capacity = atoi(argv[1]);
    int number_of_producers = atoi(argv[2]);
    int number_of_consumers = atoi(argv[3]);
    char *queue = (char *) malloc(capacity * sizeof(char));
    int head, tail = 0;
    data_t *common_data = generate_thread_parameters(queue, capacity, &head, &tail);
    pthread_t *tids = (pthread_t *) malloc((number_of_producers + number_of_consumers) * sizeof(pthread_t));
    for(i = 0; i < (number_of_producers + number_of_consumers); i++){
        if(i < number_of_producers)
            pthread_create(tids + i, NULL, producers, (void *) common_data);
        else
            pthread_create(tids + i, NULL, consumers, (void *) common_data);
    }
    for(i = 0; i < (number_of_producers + number_of_consumers); i++)
        pthread_join(*(tids + i), NULL);
    return 0;
}
