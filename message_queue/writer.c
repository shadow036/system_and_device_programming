#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_LENGTH 100
#define bool int
#define true 1
#define false 0

typedef struct{
  long int mtype;
  char mtext[MAX_LENGTH];
} message;

int main(){
  bool flag = true;
  key_t key = ftok("./key", 0);
  int message_queue_id = msgget(key, 0666 | IPC_CREAT);
  message m;
  while(flag){
    read(STDIN_FILENO, m.mtext, MAX_LENGTH * sizeof(char));
    //fscanf(stdin, "%s", m.mtext);
    if(!strcmp(m.mtext, "end"))
      flag = false;
    else{
      m.mtype = 1;
      m.mtext[strlen(m.mtext)] = '\0';
      msgsnd(message_queue_id, &m, strlen(m.mtext), 0);
    }
  }
  return 0;
}
