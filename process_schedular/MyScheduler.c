#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define max_number_of_processes 20

typedef struct process{

pid_t process_id;
time_t creation_time;
clock_t waiting_time;
clock_t processing_time;
int number_of_integers;

}process;

sem_t mutex;
int number_of_processes;
sigset_t mask, oldmask;
struct sigaction usr_action;
sigset_t block_mask;
key_t key;
int shmid;
int rtrn;
int process_no=0;
process *data;

void
synch_signal (int sig)
{
	if(sig == SIGUSR1)
	{
		sigsuspend(&mask);
	}
}

void FCFS()
{
	rtrn = shmctl(shmid, SHM_LOCK, (struct shmid_ds *) NULL);
	printf("Executing FCFS\n");
	printf("process_id : %d\n", data->process_id);
	printf("creation_time : %s\n", data->creation_time);
	printf("waiting_time : %s\n", data->waiting_time);
	printf("processing_time : %s\n", data->processing_time);
	printf("integers : %d\n", data->number_of_integers);
	data++;
	rtrn = shmctl(shmid, SHM_UNLOCK, (struct shmid_ds *) NULL);	
   
}

int main()
{

	sigemptyset (&mask);
	sigfillset(&mask);
 	sigdelset (&mask, SIGUSR2);

  	/* Establish the signal handler. */
  	sigfillset (&block_mask);
  	usr_action.sa_handler = synch_signal;
  	usr_action.sa_mask = block_mask;
  	usr_action.sa_flags = 0;
  	sigaction (SIGUSR1, &usr_action, NULL);
  	//sigaction (SIGUSR2, &usr_action, NULL);

  	/*Creating a Shared Memory Space*/
	//key = ftok("data.txt", 'R');
	shmid = shmget(5678, 1024, 0644 | IPC_CREAT);
	//char* data_t;
	data = shmat(shmid, (void *)0, 0);
	//data++;

	//data_t[0] = 'c';
	// int algo_id;
	// printf("Select scheduling algorithm\n1. FCFS\n2. SJF(Preemptive)\n3. SJF(non-preemptive)\n4. Round robin\n");
	//scanf("%d",&algo_id);
	printf("ok\n");
	data++;
	printf("process_id : %d\n", data->process_id);
	kill(data->process_id, SIGUSR2);
	// printf("goinf to wait\n");
	// raise(SIGUSR1);
	// // printf("WAITING\n");
	// FCFS();
		// else if(algo_id == 2)
		// {
		// 	SJF();
		// }
	
}