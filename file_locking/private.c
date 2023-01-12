#include "public.h"

flock_t *generate_file_lock(short type, short whence, off_t start, off_t len){
    flock_t *lock = (flock_t *) malloc(sizeof(flock_t));
    lock->l_type = type;
    lock->l_whence = whence;
    lock->l_start = start;
    lock->l_len = len;
    return lock;
}

