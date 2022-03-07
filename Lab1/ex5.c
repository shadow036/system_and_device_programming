#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define DEGREE 2
int main(int argc,char **argv){
	if(argc < 2){
		fprintf(stdout,"2 parameters expected, %d received",argc);
		return 0;
	}
	int height=atoi(argv[1]);
	int *number=(int *)malloc(height*sizeof(int));
	for(int i=0;i<height;i++){
		if(!fork())
			number[i]=1;
		else
			number[i]=0;
	}
	for(int i=height-1;i>=0;i--)
		fprintf(stdout,"%d",number[i]);
	fprintf(stdout,"\n");
	return 0;
}
