#include <bits/stdc++.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <math.h>

using namespace std;

struct timespec a,b,c,d;

void die(char *s)
{
    perror(s);
    exit(1);
}

struct listPid
{
    int child_pid[2];
    int child_size[2];
    int done[2];
};

int main()
{

    int shmid;
    key_t key,key1;
    struct listPid *tt, *lt;
    double e,f,ttt,wt;
    key = 1234;
    key1 = 1111;
    int process_id = getpid();
    

    int *spid,*pid;

    if ((shmid = shmget(key, sizeof(struct listPid), IPC_CREAT | 0666)) < 0)
        die("shmget");

    if ((tt = (struct listPid *)shmat(shmid, NULL, 0)) == (struct listPid *) -1)
        die("shmat");

    lt = tt;


    if ((shmid = shmget(key1, sizeof(int), IPC_CREAT | 0666)) < 0)
        die("shmget");

    if ((pid = (int *)shmat(shmid, NULL, 0)) == (int *) -1)
        die("shmat");

    spid = pid;
    *spid = process_id;



  //-----------------First Come First Serve Algorithm-------

   /* e=0;wt=0;tt=0;
    for(int i=0;i<2;i++)
    {
        printf("\n\nWait_Time of porcess %d is: %f second\n",i,e);
        wt = wt+e;
        clock_gettime(CLOCK_MONOTONIC,&a);
        kill(lt->child_pid[i], SIGCONT);
        kill(process_id, SIGSTOP);
        clock_gettime(CLOCK_MONOTONIC,&b);
        e=b.tv_sec - a.tv_sec+(b.tv_nsec-a.tv_nsec)/(1e9);
        ttt = ttt+e;
        printf("\n\nTime_Taken by process %d is : %f second\n",i,e);
        
    }
    printf("total time taken: %f \n",ttt);
    printf("total wait time: %f ",wt);
    */

    //-----------------Shortest job First--------------------
  /*  pair<int, int> p[2];
    for(int i=0;i<2;i++)
    {
        p[i].first = lt->child_size[i];
        p[i].second = lt->child_pid[i];
    }

    sort(p, p+2);

    for(int i=0;i<2;i++)
    {
        printf("\n\nWait_Time of porcess %d is: %f second\n",i,e);
        wt = wt+e;
        clock_gettime(CLOCK_MONOTONIC,&a);
        kill(p[i].second, SIGCONT);
        kill(process_id, SIGSTOP);
        clock_gettime(CLOCK_MONOTONIC,&b);
        e=b.tv_sec - a.tv_sec+(b.tv_nsec-a.tv_nsec)/(1e9);
        ttt = ttt+e;
        printf("\n\nTime_Taken by process %d is : %f second\n",i,e);
    }
    printf("total time taken: %f \n",ttt);
    printf("total wait time: %f ",wt);
    */

    //---------------priority scheduling--------------
    
   /* pair<int,int> p[2];
    for (int i = 0; i < 2; i++)
    {
        p[i].first = rand()%5;
        p[i].second = lt->child_pid[i];
    }

    sort(p,p+2);
    for(int i=0;i<2;i++)
    {
         printf("\n\nWait_Time of porcess %d is: %f second\n",i,e);
        wt = wt+e;
        clock_gettime(CLOCK_MONOTONIC,&a);
        kill(p[i].second, SIGCONT);
        kill(process_id, SIGSTOP);
        clock_gettime(CLOCK_MONOTONIC,&b);
        e=b.tv_sec - a.tv_sec+(b.tv_nsec-a.tv_nsec)/(1e9);
        ttt = ttt+e;
        printf("Priority: %d \n",p[i].first);
        printf("\n\nTime_Taken by process %d is: %f sec\n",i,e);
    }
    printf("total time taken: %f \n",ttt);
    printf("total wait time: %f ",wt);
    */

    //-------------round robin---------------------------

   
   for (int i = 0; i < 2; i++)
   {
       lt->done[i] = false;
   }
   int i=0;int count=0;
    while(1)
    {
        printf("\n\nWait: %f second\n",e);
        clock_gettime(CLOCK_MONOTONIC,&a);
        kill(lt->child_pid[i], SIGCONT);
        sleep(1);
        kill(lt->child_pid[i], SIGSTOP);
        clock_gettime(CLOCK_MONOTONIC,&b);
        e=b.tv_sec - a.tv_sec+(b.tv_nsec-a.tv_nsec)/(1e9);
        ttt = ttt+e;
        //printf("Priority: %d \n",p[i].first);
        printf("\n\nTime_Taken by process %d is: %f sec\n",i,e);
        if(lt->done[i]==true)
        {
            count++;
        }
        if(count==2)
        {
            break;
        }
        i = (i+1)%2;

    }
    

    return 0;
}
