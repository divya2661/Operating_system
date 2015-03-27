#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/* Size and dimensions of Matrices, and the thread pool */
int row1, col1, row2, col2, currentRow = 0, currentCell = 0,flag, Matrix1[5005][5005], Matrix2[5005][5005], Result_Mat[5005][5005];
pthread_t * threads;
int numberOfThreads;

/* Mutex for the currentRow and currentCell. */
pthread_mutex_t mutex_Cell = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER;

void prmat()
{
    // Print resultant matrix
    int i, j;
      printf("\n MAtrix-1:\n");
    for (i = 0; i < row1; i++)
    {
        
        for (j = 0; j < col1; j++)
        {
            printf("%d ", Matrix1[i][j]);

        }
        printf("\n");
        
    }
      printf("\nMAtrix-2:\n");
    for (i = 0; i < row2; i++)
    {
        
        for (j = 0; j < col2; j++)
        {
            printf("%d ", Matrix2[i][j]);

        }
        printf("\n");
        
    }
    printf("\nFinal MAtrix:\n");
    for (i = 0; i < row1; i++)
    {
        
        for (j = 0; j < col2; j++)
        {
            printf("%d ", Result_Mat[i][j]);

        }
        printf("\n");
        
    }
}

void* thread_func(int Id)
{
    int i, j, myCell, cnt;
    while (1)
    {
        
        pthread_mutex_lock(&mutex_Cell);
        if (currentCell >= row1*col2)
        {
            pthread_mutex_unlock(&mutex_Cell);
            
            if (Id == 0)
                return;
            pthread_exit(0);
        }
        myCell = currentCell;
        currentCell++;
        pthread_mutex_unlock(&mutex_Cell);

        i = myCell/col2, j = myCell%col2;
        if(i==row1-1 && j==col1-1){flag=1;}
        for (cnt = 0; cnt < col1; cnt++)
            Result_Mat[i][j] += Matrix1[i][cnt] * Matrix2[cnt][j];
    }
}

int main()
{       
    // Hold for Threads. pthread_t *threads; int numberOfThreads;
    int i, j, k;
    system("clear");
    freopen("input.txt", "r", stdin);
    /*freopen("output.txt", "w", stdout);*/
    
    scanf("%d%d",&row1,&col1);
    scanf("%d%d",&row2,&col2);
    
    if (col1 != row2)
    {
        printf("col1 and row2 are not equal can't multiply.\n");
        fclose(stdin);
        /*fclose(stdout);*/
        return 0;
    }


    scanf("%d",&numberOfThreads);
    
    printf("Total threads: %d\n\n", numberOfThreads);
    

    /* Populate the Matrices. */ 
    for (i = 0; i < row1; i++)
    {
        for (j = 0; j < col1; j++)
            scanf("%d", &Matrix1[i][j]);
    }
    printf("\n");
    for (i = 0; i < row2; i++)
    {
        for (j = 0; j < col2; j++)
            scanf("%d", &Matrix2[i][j]);
    }


    
    struct timespec st, en;
/*_________________________________CELL-WISE_________________________________________*/
    
// Initialize resultant matrix
    for (i = 0; i < row1; i++)
        for (j = 0; j < col2; j++)
            Result_Mat[i][j] = 0;
    

    // create the desired number of threads
    threads = (pthread_t *) malloc(sizeof(pthread_t) * numberOfThreads);
    
    // Start Distributing the work.
    currentRow = 0, currentCell = 0,flag=0;
    
    clock_gettime(CLOCK_MONOTONIC, &st);
    
    for (i=1; i<numberOfThreads; i++)
       { 

       		if(flag==0)
       		{
       			printf("need more thread\n");
       			pthread_create(&threads[i], NULL, (void *(*) (void *))thread_func, (void *) (i+1));
       		}
       		else{
       			printf("we are done. no more threads required.\n");
       		}
       		
       	}
    
    for (i = 0; i < numberOfThreads; i++)
        {
        	pthread_join(threads[i], NULL);
        }

    clock_gettime(CLOCK_MONOTONIC, &en);
    //prmat();
    
    printf("multithreading: %f secs.\n", en.tv_sec - st.tv_sec + (en.tv_nsec - st.tv_nsec)/1.0e9);


    
    for (i = 0; i < row1; i++)
        for (j = 0; j < col2; j++)
            Result_Mat[i][j] = 0;
    
    clock_gettime(CLOCK_MONOTONIC, &st);

    for(i=0; i<row1; i++)
    {
        for(j=0; j<col2; j++)
        {
            for(k=0; k<col1; k++)
            {
                Result_Mat[i][j] += Matrix1[i][k] * Matrix2[k][j];
            }
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, &en);
    printf("without multithreading: %f secs.\n", en.tv_sec - st.tv_sec + (en.tv_nsec-st.tv_nsec)/1.0e9);

    prmat();

/*_____________________________________________________________________________________*/

    fclose(stdin);
    fclose(stdout);
    return 0;
}
