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
  printf("\nbefore writer: %p => %c", address, *address);
  sleep(10);
  printf("\nafter writer: %p => %c\n", address, *address);
  shmdt(address);
  shmctl(id, IPC_RMID, NULL);
  return 0;
}
