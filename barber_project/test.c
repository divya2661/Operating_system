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
    //int creating_time;
    int process_id;
    int brust_time;
}table_str;

/* Child doing all processes */
void sleep_process(int i)
{
   printf("        Sleeping :  %d.\n",i);
   raise(SIGUSR1);

   printf("wake up process...\n");
   

}
// void wake_process(int process_no)
// {
//     printf("waking up...gd morning.. =D\n");
//     raise(SIGUSR2);

// }


void Sleep_signal(int signal)
{
    sigset_t sig_set;
     /*The sigfillset(int *set) function shall initialize the signal 
     set pointed to by set, such that all signals defined in 
    this volume of IEEE Std 1003.1-2001 are included.*/
    sigfillset(&sig_set);           /*(Filled the set with all signals)              It allows you to send your thread to sleep */
    sigdelset(&sig_set, SIGUSR2);   /* (Delete that perticular signal we want to use)until one of its selected signals occurs. */
    sigsuspend(&sig_set);           /*(suspended process for all other signals)       If you want it to sleep until SIGUSR2 arrives*/
    


}

table_str init_child(int proc_no,int b_time)
{
    printf("                Stoderd in shared memory table--process--> %d\n", proc_no);

    table_str child_str;
    child_str.process_no = proc_no;
    child_str.brust_time = b_time;
    child_str.process_id = getpid(); 

    return(child_str);
}


int main()
{       
    
    int parent_pid;
    int i,c,j;
    int pid[No_P];
    int status;
    int shmid;
    int rand_no;
    int signal_sigu1;
    int signal_sigu2;
    sem_init(&mutex,0,1);

    /* ----------Creating shared memory segment-------*/
    table_str table;
    table_str *t_shm;
    shmid = shmget(IPC_PRIVATE,2048,IPC_CREAT | 0666);
    if(shmid<0){
        printf("Failed to create shared memory.\n");
        exit(1);
    }
    t_shm = shmat(shmid,NULL,0);

    /*-----Creating Signal Handlers-----*/

    signal_sigu1 = signal(SIGUSR1,Sleep_signal);
    signal_sigu2 = signal(SIGUSR2,wake_process);
    if(signal_sigu1==SIG_ERR)
    {
        printf("Unable to create signal SIGUSR1 handler. :( \n");
        exit(0);
    }
    if(signal_sigu2==SIG_ERR)
    {
        printf("Unable to create signal SIGUSR2 handler. :( \n");
        exit(0);
    }
    
    /* Creating child processes*/
    printf("[---------------Forking Child-----------------] \n");    
    for (i = 0; i < No_P; i++)
    {
        pid[i] = fork();
        if(pid[i] < 0)
        {
            printf("couldn't create the process. forking failed\n");
        }
        else if(pid[i] == 0)
        {
            printf("Created process: %d having process id: %d\n",i,getpid());
            rand_no = rand()%20;
            table = init_child(i,rand_no); //can give creation time as well
            sleep_process(i);
            sem_wait(&mutex);
                t_shm[i] = table;
            sem_post(&mutex);
            exit(0);
        }
    }

    c = wait(&status);        
    return(0);
}
