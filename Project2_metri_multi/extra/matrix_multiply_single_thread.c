#include <stdio.h>
#include <pthread.h>
 int mat1[10][10];
 int mat2[10][10];
 int mat3[10][10];
 int r1,c1,r2,c2;

 void *thread_multiply_matrix(void*);

 int main(int argc, char const *argv[])
 {
 	pthread_t tid;
 	int i,j,k;

 	printf("Enter no. of rows for matrix-1: ");
 	scanf("%d",&r1);

 	printf("Enter no. of cols for matrix-1: ");
 	scanf("%d",&c1);


 	for (i = 0; i < r1; i++)
 	{
		for (j = 0; j < c1; j++)
			{
				printf("Enter mat1[%d][%d]: ",i,j);
				scanf("%d",&mat1[i][j]);
			}	

		
 	}

 	printf("Enter no. of rows for matrix-2: ");
 	scanf("%d",&r2);

 	printf("Enter no. of cols for matrix-2: ");
 	scanf("%d",&c2);

 	for (i = 0; i < r1; i++)
 	{
		for (j = 0; j < c1; j++)
			{
				printf("Enter mat2[%d][%d]: ",i,j);
				scanf("%d",&mat2[i][j]);
			}	
		
 	}
 	printf("\n");
 	printf("Matrix Generated.\n");
 	printf("\n");
 	printf("Matrix--1\n");
 	for (i = 0; i < r1; i++)
 	{
		for (j = 0; j < c1; j++)
			{
				printf(" %d ",mat1[i][j]);
				
			}	
			printf("\n");
		
 	}

 	printf("\n");
 	printf("Matrix--2\n");
 	for (i = 0; i < r2; i++)
 	{
		for (j = 0; j < c2; j++)
			{
				printf(" %d ",mat2[i][j]);
				
			}
			printf("\n");
		
 	}
 	if(c1!=r2)
 	{
 		printf("Matrix can not be multiplied.\n");
 	}
 	else
 	{
 		for(i=0;i<r1;i++)
	 	{
	 		for(j=0;j<c2;j++)
	 		{
	 			mat3[i][j]=0;
	 		}
	 	}
	 	pthread_create(&tid,NULL,thread_multiply_matrix,NULL);
	 	for(i=0;i<r1;i=i+2)
	 	{
	 		for(j=0;j<c2;j++)
	 		{
	 			for(k=0;k<c1;k++)
	 			{
	 				mat3[i][j] = mat3[i][j]+(mat1[i][k]*mat2[k][j]);
	 			}
	 		}
	 	}
	 	pthread_join(tid,NULL);
 	}

 	printf("\n");
 	printf("Multiplied Matrix\n");
 	for (i = 0; i < r1; i++)
 	{
		for (j = 0; j < c2; j++)
			{
				printf(" %d ",mat3[i][j]);
				
			}
			printf("\n");
		
 	}

 	return 0;
 }

 void *thread_multiply_matrix(void *para)
 {
 	printf("nctionentering in thread fu\n");
 	int i,j,k;
 	for(i=1;i<r1;i=i+2)
 	{
 		for (j=0; j < c2;j++)
 		{
 			for(k=0;k<c1;k++)
 			{
 				mat3[i][j] = mat3[i][j]+mat1[i][k]*mat2[k][j];
 			}
 		}
 	}
 	printf("Exiting thread...\n");
 	pthread_exit(NULL);

 }