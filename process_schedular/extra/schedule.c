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
#define No_P 10
sem_t mutex;
//#include <time.h>
typedef struct{
    int process_no;
    int process_id;
    int brust_time;
}table_str;
int main()
{       
    int shmid;
    int rand_no;
    int signal_sigu1;
    int signal_sigu2;
    sem_init(&mutex,0,1);
    int key =7777;

    /* ----------Creating shared memory segment-------*/
    table_str table;
    table_str *t_shm;
    shmid = shmget(key,2048,IPC_CREAT | 0666);
    if(shmid<0){
        printf("Failed to create shared memory.\n");
        exit(1);
    }
    t_shm = shmat(shmid,NULL,0);
    printf("scheduler.....\n");
    while(t_shm->process_no!=8){
    	printf("table[%d]: process_id: %d brust_time: %d\n",t_shm->process_no,t_shm->process_id,t_shm->brust_time );    
    	t_shm++;rand_no rand_no = rand()%20;= rand()%20;
    }


  
          
    return(0);
}
