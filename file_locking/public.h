#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef struct flock flock_t;

flock_t *generate_file_lock(short, short, off_t, off_t);
