#include "public.h"

int main(int argc, char **argv){
    int i = 0;
    int cars_on_the_left = atoi(argv[1]);
    int cars_on_the_right = atoi(argv[2]);
    int cars_transiting_from_the_left, cars_transiting_from_the_right = 0;
    lr_t *lr = generate_lr(&cars_transiting_from_the_left);
    rl_t *rl = generate_rl(&cars_transiting_from_the_right, lr);
    pthread_t *ids_left = (pthread_t *) malloc(cars_on_the_left * sizeof(pthread_t));
    pthread_t *ids_right = (pthread_t *) malloc(cars_on_the_right * sizeof(pthread_t));
    for(i = 0; i < cars_on_the_left; i++)
        pthread_create(ids_left + i, NULL, move_lr, lr);
    for(i = 0; i < cars_on_the_right; i++)
        pthread_create(ids_right + i, NULL, move_rl, rl);

    for(i = 0; i < cars_on_the_left; i++)
        pthread_join(ids_left[i], NULL);
    for(i = 0; i < cars_on_the_right; i++)
        pthread_join(ids_right[i], NULL);
    return 0;
}
