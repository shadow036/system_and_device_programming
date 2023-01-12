#include "public.h"

int main(int argc, char **argv){
    int fd = open("lab01.txt", O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR);
    pid_t pid;
    if((pid = fork()) > 0){
        flock_t *lock = generate_file_lock(F_WRLCK, SEEK_SET, 0, 1000);
        fcntl(fd, F_GETLK, lock);
        if(lock->l_type == F_UNLCK){
            fprintf(stdout, "\n%d can obtain write lock\n", getpid());
            lock->l_type = F_WRLCK;
            int return_value = fcntl(fd, F_SETLK, lock);
            if(return_value == EACCES || return_value == EAGAIN)
                fprintf(stdout, "\nunknown error\n");
            else
                fprintf(stdout, "\n%d has obtained the write lock\n", getpid());
        }else
            fprintf(stdout, "\n%d cannot obtain the write lock: it is currently held by process %d\n", getpid(), lock->l_pid);
        wait(NULL); // it waits the other process but it cannot go on since it needs the lock currently held by this one => deadlock
    }else{
        sleep(2);
        flock_t *lock = generate_file_lock(F_RDLCK, SEEK_SET, 5, 1500);
        fcntl(fd, F_GETLK, lock);
        if(lock->l_type == F_UNLCK){
            fprintf(stdout, "\n%d can obtain read lock\n", getpid());
            lock->l_type = F_RDLCK;
            int return_value = fcntl(fd, F_SETLK, lock);
            if(return_value == EACCES || return_value == EAGAIN)
                fprintf(stdout, "\nunknown error\n");
            else
                fprintf(stdout, "\n%d has obtained the read lock\n", getpid());
        }else
            fprintf(stdout, "\n%d cannot obtain the read lock: it is currently held by process %d\n", getpid(), lock->l_pid);
    }
    return 0;
}
