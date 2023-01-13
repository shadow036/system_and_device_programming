#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SHARED_MEMORY_SIZE 1024

int main(){
  key_t k = ftok("./shared_memory_key", 0);
  int id = shmget(k, SHARED_MEMORY_SIZE, 0666 | IPC_CREAT);
  char *address = shmat(id, NULL, 0);
  sleep(5);
  *address = 'a';
  printf("\nwrote 'a' at address %p\n", address);
  shmdt(address);
  shmctl(id, IPC_RMID, NULL);
  return 0;
}
