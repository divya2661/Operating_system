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


int number_of_processes;
sigset_t mask, oldmask;
struct sigaction usr_action;
sigset_t block_mask;
key_t key;
int shmid,shmid_m;
int rtrn;
process *data;
pthread_mutex_t mutex;
sem_t sem;

void
synch_signal (int sig)
{
	if(sig == SIGUSR1)
	{
		sigsuspend(&mask);
	}
}

int comp(const void *a,const void *b) {
int *x = (int *) a;
int *y = (int *) b;
return *x - *y;
}

/* The child process executes this function. */
void
child_process (int number)
{

	printf("created %d\n",(int)getpid() );
	raise(SIGUSR1);
	printf ("I'm here!!!  My pid is %d.\n", (int) getpid ());

	int i=0;
	int process_numbers[number];
	for(i=0;i<number;i++)
	{
			process_numbers[i] = rand()%100 +1;
	}
	qsort (process_numbers, sizeof(process_numbers)/sizeof(*process_numbers), sizeof(*process_numbers),comp);
	for(i=0;i<number;i++)
	{
			printf("number %d is %d\n",i,process_numbers[i] );
	}
	exit (0);
}

process create_process_structure(int integer)
{
	process *pr = malloc(sizeof(process));
	process pro = *pr;
	pro.process_id = getpid();
	pro.creation_time =  clock();
	pro.processing_time = (clock_t)0;
	pro.waiting_time = (clock_t)0;
	pro.number_of_integers = integer;

	return pro;
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
  	sigaction (SIGUSR2, &usr_action, NULL);

  	/*Creating a Shared Memory Space*/
	//key = ftok("data.txt", 'R');
	shmid = shmget(5678, 1024, 0644 | IPC_CREAT);
	data= shmat(shmid, (void *)0, 0);
	//data = data + (process)data_t;
	//printf("DONE %c\n",data_t[0]);
	pthread_mutex_init(&mutex,NULL);
	sem_init(&sem,0,1);
	sem_t *data_t;
	//pthread_mutex_t* data_t;
	shmid_m = shmget(5679,1*sizeof(sem_t), 0644 | IPC_CREAT);
	data_t = shmat(shmid, (void *)0, 0);
	data_t[0] = sem;


	int i;
	printf("Enter number of processes to be created\n");
	scanf("%d",&number_of_processes);
	pid_t child_pid;

	for(i=0;i<number_of_processes;i++)
	{
		child_pid = fork();
		if(child_pid == 0)
		{
			static int process_no;
			printf("waiting here\n");
			sem_wait(data_t);
			//pthread_mutex_lock(data_t);
			int integer = rand()%100 + 1;
			process pro = create_process_structure(integer);
			process_no = data[0].number_of_integers;
			printf("process_no %d\n", process_no );
  			data[process_no] = pro;
  			process_no++;
  			data[0].number_of_integers = process_no;
  			printf("going out\n");
  			sem_post(data_t);
  			// pthread_mutex_unlock(data_t);
			child_process(integer);
		}
		//sleep(1);
	}
	
	int d;

	for(d=0;i<number_of_processes;d++)
	{
		//rtrn = shmctl(shmid, SHM_LOCK, (struct shmid_ds *) NULL);
		printf("Executing FCFS\n");
		printf("process_id : %d\n", data->process_id);
		printf("creation_time : %s\n", data->creation_time);
		printf("waiting_time : %s\n", data->waiting_time);
		printf("processing_time : %s\n", data->processing_time);
		printf("integers : %d\n", data->number_of_integers);
		data++;
		//rtrn = shmctl(shmid, SHM_UNLOCK, (struct shmid_ds *) NULL);
	}

	int status;
	wait(&status);
	return 0;
}