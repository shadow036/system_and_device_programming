#include "public.h"
#include <pthread.h>

int main(int argc, char **argv){
    if(argc != 2){
        write(STDOUT_FILENO, "wrong number of parameters", sizeof("wrong number of parameters"));
        return -1;
    }
    int capacity = atoi(argv[1]);
    char *queue = (char *) malloc(capacity * sizeof(char));
    int head, tail = 0;
    pthread_t tids[2];
    data_t *common_data = generate_thread_parameters(queue, capacity, &head, &tail);
    pthread_create(tids, NULL, producer, (void *) common_data);
    pthread_create(tids + 1, NULL, consumer, (void *) common_data);
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    return 0;
}
