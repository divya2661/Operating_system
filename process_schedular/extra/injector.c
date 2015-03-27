#include<stdio.h>
#include<signal.h>
#include<semaphore.h>
#include"MyScheduler.c"
int createpseodo(int kk,sem_t mutex2)
{
    int k=(int)kk;
    int a[k];
    int i=0;
    for(i=0;i<k;i++)
    a[i]=rand()%100;int pass,hold;
    for(pass = 1; pass <= (k-1); pass++)
            for(i = 0; i <= (k-2); i++)
              if(a[i] > a[i + 1])
              {
                     hold = a[i];
                     a[i] = a[i + 1];
                     a[i + 1] = hold;
              }
              printf("\n\nData items in ascending order :\n\n");
       for (i=0; i <= (k-1); i++)
            printf("%4d", a[i]);
       printf("\n\n");
}
void sigusr1(int pid)
{
    kill(pid,SIGUSR1);
}
void sigusr2(int pid)
{
    kill(pid,SIGUSR2);
}
int main()
{
	sem_t mutex,mutex2;
    sem_init(&mutex, 0, 1);sem_init(&mutex2, 0, 1);
    printf("Enter number of processes : ");
    int n,status=0;
    scanf("%d",&n);
	int a[n],ti[n],p[n];
    int i,i1,d=getpid();
    for(i=1;i<=n;i++)
	{
		printf("Enter ti and pi for next process : ");
		scanf("%d%d",&ti[i-1],&p[i-1]);
	}
    for(i=1;i<=n;i++)
    {
    	int p=fork();
    	if(p==0)
    	{
			sem_wait(&mutex);
			sleep(1);
    		kill(getpid(),SIGSTOP);
			i1=i-1;
			sem_post(&mutex);
			break;
    	}
		a[i-1]=p;
    }
	int t=getpid();
	if(d==t)
	{
		printf("Parent\n");
		main2(p,ti,a,n);
	}
	else
	{
		printf("Child %d\n",t);
		printf("%d ti\n",ti[i1]);
		createpseodo(ti[i1],mutex2);
		
	}
	for(i=0;i<n;i++)
	{
		if(d==getpid())
		{
			printf("p : %d\n",a[i]);
		}
	}
    return 0;
}
