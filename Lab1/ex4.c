#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv){
	if(argc<3){
		fprintf(stdout,"3 parameters expected, %d received\n",argc);
		return 0;
	}
	int height=atoi(argv[1]);
	int degree=atoi(argv[2]);
	for(int i=0;i<=height;i++){
		for(int j=0;j<degree-1;j++){
			if(!fork())
				break;	
		}
	}
	fprintf(stdout,"Process %d terminated\n",getpid());
	return 0;
}
