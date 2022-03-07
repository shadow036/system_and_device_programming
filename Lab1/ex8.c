#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void mat_mul(int **, int **, int, int, int, int **);
void *compute(int **, int **, int, int, int, int, int **);
int **tids;
int main(int argc,char **argv){	//receives 3 additional arguments: #rows first matrix, #columns first matrix, #columns second matrix
	if(argc < 4){
		fprintf(stdout,"4 parameters expected, %d received\n",argc);
		return 0;
	}
	int rows1=atoi(argv[1]);
	int common=atoi(argv[2]);
	int columns2=atoi(argv[3]);
	int i,j;
	int **m1=(int **)malloc(rows1*sizeof(int *));
	int **m2=(int **)malloc(common*sizeof(int *));
	int **m3=(int **)malloc(rows1*sizeof(int *));
	tids=(int **)malloc(rows1*sizeof(int *));
	for(i=0;i<rows1;i++){
		m1[i]=(int *)malloc(common*sizeof(int));
		for(j=0;j<common;j++){
			fprintf(stdout,"M1[%d][%d]=>",i,j);
			fscanf(stdin,"%d",&m1[i][j]);
		}
	}
	for(i=0;i<common;i++){
		m2[i]=(int *)malloc(columns2*sizeof(int));
		for(j=0;j<columns2;j++){
			fprintf(stdout,"M2[%d][%d]=>",i,j);
			fscanf(stdin,"%d",&m2[i][j]);
		}
	}
	for(i=0;i<rows1;i++){
		m3[i]=(int *)malloc(columns2*sizeof(int));
		tids[i]=(int *)malloc(columns2*sizeof(int));
		for(j=0;j<columns2;j++)
			m3[i][j]=0;
	}
	mat_mul(m1,m2,rows1,common,columns1,m3);
	return 0;
}
void mat_mul (int **A, int **B, int r, int x, int c, int **C){
	for(i=0;i<rows1;i++){
		for(j=0;j<columns1;j++){
			pthread_create(&tids[i][j],NULL,compute,
		}	
	}
}