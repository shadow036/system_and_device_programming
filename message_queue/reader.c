#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100

typedef struct{
  long int mtype;
  char mtext[MAX_LENGTH];
} message;

int main(){
  message m;
  key_t key = ftok("./key", 0);
  int message_queue_id = msgget(key, 0666 | IPC_CREAT);
  while(36){
    msgrcv(message_queue_id, &m, MAX_LENGTH * sizeof(char), 1, 0);
    printf("received %s", m.mtext);
  }
  return 0;
}
