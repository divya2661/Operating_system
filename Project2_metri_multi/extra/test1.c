#include <stdio.h>
#include <pthread.h>
 int NUM_THREADS;
 int mat1[10][10];
 int mat2[10][10];
 int mat3[10][10];

 int r1,c1,r2,c2;

 void *thread_multiply_matrix(void*);

 int main(int argc, char const *argv[])
 {
 	int i,j,k;
 	long t;

 	printf("Enter number of threads: ");
scanf("%d",&NUM_THREADS);

 	pthread_t tid[NUM_THREADS];

 	
 	
 	

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
	 	for(t=1;t<NUM_THREADS;t++)
	 	{
	 		pthread_create(&tid[t],NULL,thread_multiply_matrix,(void*)t);
	 		
	 	}

	 	for(i=0;i<r1;i=i+NUM_THREADS)
	 	{
	 		for(j=0;j<c2;j++)
	 		{
	 			for(k=0;k<c1;k++)
	 			{
	 				mat3[i][j] = mat3[i][j]+(mat1[i][k]*mat2[k][j]);
	 			}
	 		}
	 	}
	 	for(t=1;t<NUM_THREADS;t++)
	 	{
	 		
	 		pthread_join(tid[t],NULL);
	 	}
	 	
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
 	
 	int i,j,k;
 	long id;
 	id = (long)para;
 	 printf("Thread # %ld created this: \n", id);
 	for(i=id;i<r1;i=i+NUM_THREADS)
 	{
 		for (j=0; j < c2;j++)
 		{
 			for(k=0;k<c1;k++)
 			{
 				mat3[i][j] = mat3[i][j]+mat1[i][k]*mat2[k][j];

 			}
 			printf("  %d",mat3[i][j] );
 		}
 		
 	}
 	printf("\n");
 	printf("Exiting thread...\n");
 	pthread_exit(NULL);

 }