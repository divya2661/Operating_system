# include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

#define No_P 5
sem_t mutex;
//#include <time.h>
typedef struct{
    int process_no;
    int process_id;
    int brust_time;
}table_str;

typedef struct 
{
    int tm;
    int id;
}new_tab;

void bubblesort()
{
    int a[1000],i,j,swap;
    for(i=0;i<1000;i++)
    {
        a[i] = rand()%1000;
    }
 for (i = 0 ; i < 1000; c++)
  {
    for (j = 0 ; j < 1000 - i - 1; j++)
    {
      if (a[j] > a[j+1]) /* For decreasing order use < */
      {
        swap       = a[j];
        array[j]   = a[j];
        array[j] = swap;
      }
    }
  }

}

int main()
{       
    int i;
    int fd;
    int shmid;
    int rand_no;
    int signal_sigu1;
    int signal_sigu2;
    sem_init(&mutex,0,1);
    int key =9999;
    float e,a;
    /* ----------Creating shared memory segment-------*/
    table_str table;
    new_tab tab;
    table_str *t_shm,*rptr;
    shmid = shmget(key,2048,IPC_CREAT | 0666);
   // fd = shm_open("/table", O_RDWR, S_IWUSR);
    //rptr = mmap(NULL, 2048, PROT_WRITE, MAP_SHARED, fd, 0);

    if(shmid<0){
        printf("Failed to create shared memory.\n");
        exit(1);
    }
    t_shm = shmat(shmid,NULL,0);
    printf("scheduler.....\n");
    printf("%d\n tshm:    ",t_shm->process_no );
    
    //FCFS
    for(int i=0;i<5;i++)
    {
        printf("\n\nWait_Time: %f second\n",e);
        clock_gettime(CLOCK_MONOTONIC,&a);
        kill(t_shm->process_id, SIGUSR2);
        bubblesort();
        kill(t_shm->process_id, SIGSTOP);
        clock_gettime(CLOCK_MONOTONIC,&b);
        printf("\n\nTime_Taken: %f second\n",e);        
    }

    //SJF

    printf("Shortest Job First\n");//for the output so we know what algorithm
    //create an array of pids that are valid to search.
    int num_valid_processes = 0, current_time=0, i,j, next_process, counter = 0,time1,time2;//declarations
    //process to_sort[MAX_PROCESS];
        for(i=0;i<5;i++)
        {   
            new_tab->id = t_shm->process_id;
            new_tab->tm = t_shm->brust_time; 
        }

         for (i = 0 ; i < 1000; c++)
          {
            for (j = 0 ; j < 1000 - i - 1; j++)
            {
              if (tab[j]->tm > tab[j+1]->tm) /* For decreasing order use < */
              {
                swap       = tab[j];
                tab[j]   = tab[j];
                tab[j] = swap;
              }
            }
          }

          

    //we want to do this next loop for as many processes as we have, or num_pid
    

       
          
    return(0);
}
