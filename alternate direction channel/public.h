#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct lr_s lr_t;
typedef struct rl_s rl_t;

lr_t *generate_lr(int *);
rl_t *generate_rl(int *, lr_t *);
void *move_lr(void *);
void *move_rl(void *);
