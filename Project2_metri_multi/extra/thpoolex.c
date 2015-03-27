#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"
#include "thpool.c"
#define Max_no_of_threads 1000

int A[20][20];
int B[20][20];
int C[20][20];
int r1,c1,r2,c2;
int rn=0,cn=0,fn=0;
int lrc=0;
int input[30];
void multiply()
{
	printf("Thread #%u working on task3\n",(int)pthread_self());
	int k;

	
	//for(i=0;i<r1;i++)
	//{

	if(rn<r1&&rn>=0)
	{
		if(cn<c2&&cn>=0)
		//for(j=0;j<c2;j++)
		{
			for(k=0;k<c1;k++)
			{
				C[rn][cn]+=A[rn][k]*B[k][cn];
			}

		}
		cn++;
	lrc++;
	/*printf("lrc=%d\n",lrc);
	printf("c2=%d\n",c2);*/
	if(lrc==(c2))
	{
		//printf("entered1");
	rn++;
	lrc=0;
	}

	}
	if(cn==c2)
	{
		cn=0;
	}


		/*printf("rn=%d\n",rn);
	printf("cn=%d\n",cn);
	printf("lrc=%d\n",lrc);*/


	//}
}

int main()
{
	int bufcount=0;
	FILE *input_file=fopen("input.txt","r");
	char buff[1000];
	if(!input_file)
		return 1;
	while(fgets(buff,1000,input_file)!=NULL)
	{
		input[bufcount]=atoi(buff);
		bufcount++;
	}
	//printf("enter the values of r1,c1,r2,c2\n");
	//scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
	r1=input[0],c1=input[1],r2=input[2],c2=input[3];
	if(c1!=r2)
	{
		printf("matrix multiplication cannot be done for this order");
		return;
	}
	int i,j;
	//printf("enter the elements in to matrix 1\n");
	int mat1=4;
	for(i=0;i<r1;i++)
	{
		for(j=0;j<c1;j++)
		{
			//scanf("%d",&A[i][j]);
			A[i][j]=input[mat1];
			mat1++;
		}
	}
	printf("Elements of matrix 1 are \n");
	for(i=0;i<r1;i++)
	{
		for(j=0;j<c1;j++)
		{
			printf("%d\t",A[i][j]);
		}
		printf("\n");
	}
//	printf("enter the elements in to matrix 2\n");
	for(i=0;i<r2;i++)
	{
		for(j=0;j<c2;j++)
		{
			//scanf("%d",&B[i][j]);
			B[i][j]=input[mat1];
			mat1++;
		}
	}
	printf("elements of matrix 2 are\n");
	for(i=0;i<r2;i++)
	{
		for(j=0;j<c2;j++)
		{
			printf("%d\t",B[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<r1;i++)
	{
		for(j=0;j<c2;j++)
		{
			C[i][j]=0;
		}
	}
	int n1;
	//printf("enter the number of threads");
	//scanf("%d",&n1);
	n1=input[mat1];
	if(n1<1||n1>Max_no_of_threads)
	{
		printf("More than the Max_no_of_threads");
		return;
	}
	
	printf("Making threadpool with %d threads\n",n1);
	threadpool thpool = thpool_init(n1);

	//puts("Adding 40 tasks to threadpool");
	int i1;
	/*for (i1=0; i1<5; i1++)
	{
		printf("entered\n");
		thpool_add_work(thpool, (void*)task1, NULL);
		thpool_add_work(thpool, (void*)task2, NULL);
	};*/
	for (i1=0; i1<(r1*c2); i1++)
	{
	thpool_add_work(thpool, (void*)multiply,NULL);
	};


	int j1;

thpool_wait(thpool);
	puts("Killing threadpool");
	thpool_destroy(thpool);
	//printf("i1=%d\n",i1);
	for(i1=0;i1<r1;i1++)
	{
		for(j1=0;j1<c2;j1++)
		{
			printf("%d\t",C[i1][j1]);
		}
		printf("\n");
	}

	
	return 0;
}