#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int sm1[2];
int sm2[3];
void handler(int sig){
	sm1[0]=sm1[1];
	sm2[0]=sm2[1];
	sm2[1]=sm2[2];
	if(sig==SIGUSR1){
		sm1[1]=1;
		sm2[2]=1;
	}else if(sig==SIGUSR2){
		sm1[1]=2;
		sm2[2]=2;
	}
	if(sm2[0]==sm2[1] && sm2[1]==sm2[2])
		exit(EXIT_FAILURE);
	if(sm1[0]+sm1[1]==3)
		fprintf(stdout,"success\n");
	if(sm1[0]==sm1[1])
		fprintf(stdout,"error\n");
}
int main(){
	signal(SIGUSR1,handler);
	signal(SIGUSR2,handler);
	sm1[0]=0;
	sm1[1]=0;
	sm2[0]=0;
	sm2[1]=0;
	sm2[2]=0;
	while(1);
	return 0;
}
