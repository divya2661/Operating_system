#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5

void *PrintHello(void *threadid)
{
	long taskid;
	sleep(1);
	taskid = *(long*)threadid;
	printf("hello from thread--%ld\n",taskid );
	pthread_exit(NULL);
}
int main(int argc, char const *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc,t;

	for (t = 0;t<NUM_THREADS; t++)
	{
		printf("Creating thread: %d\n", t);
		rc = pthread_create(&threads[t],NULL,PrintHello,(void*)t);
		if(rc){
			printf("error...............\n");
		}

	}
	pthread_exit(NULL);
	
}