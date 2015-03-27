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
#include <stdint.h>
#include <random>

using namespace std;

struct listPid
{
    int child_pid[2];
    int child_size[2];
    int done[2];
};

void die(char *s)
{
    perror(s);
    exit(1);
}

class Process
{
    public:
        void waiting();
        void resume();
        void task();
        int getPid();
        static void signalHandler(int sig);
        int array_size;
        Process();
};

Process::Process(void)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    array_size = (dis(gen))*10000;
}

void Process::waiting()
{
    kill(getpid(), SIGSTOP);
}

void Process::resume()
{
    kill(getpid(), SIGCONT);
}

void Process::task()
{

    waiting();
    int shmid;
    key_t key1 = 1111;
    int *spid,*pid;
    struct listPid *lt, *tt;
    if ((shmid = shmget(key1, sizeof(int), IPC_CREAT | 0666)) < 0)
        die("shmget");

    if ((pid = (int *)shmat(shmid, NULL, 0)) == (int *) -1)
        die("shmat");

    spid = pid;

    cout<<"Process with "<<getPid()<<" begins\n";

    int t = array_size; // `random number between 100 to 1000
    cout<<"array_size:"<<t<<endl;
    int a[t];
    for(int i=0;i<t;i++)
    {
        a[i] = (rand()%10);
    }
    int i,j;
    for(i=0;i<t;i++)
    {
        for(j=i+1;j<t;j++)
        {
            if(a[j]<a[i])
            {
                swap(a[i],a[j]);
            }
        }
    }
    cout<<"Process with "<<getpid()<<" done !!! "<<endl;
    // for (int i = 0; i < 2; i++)
    // {
    //     if(lt->done[i]==getpid())
    //     {
    //         lt->done[i] = true;
    //     }
    // }
    kill(*spid, SIGCONT);

}

int Process::getPid()
{
    return getpid();
}



class ProcessTableList
{
    public:
        int addProcess();
        //void removeProcess(pid_t pid);
};

int ProcessTableList::addProcess()
{
    pid_t child = fork();

    if(child == 0)
    {
        Process p;
        sem_t * sem = sem_open ( "semname" , O_CREAT | O_EXCL , S_IRUSR | S_IWUSR , 0) ;
        if ( sem != SEM_FAILED )
            printf ( " created new semaphore !\n " ) ;
        else if ( errno == EEXIST )
        {
            sem = sem_open ( "semname" , 0) ;
        }

        int shmidi;
        key_t counter_key;

        int *counter, *t_counter;

        counter_key = 1000;

        if ((shmidi = shmget(counter_key, sizeof(int), IPC_CREAT | 0666)) < 0)
            die("shmget");

        if ((counter = (int *)shmat(shmidi, NULL, 0)) == (int *) -1)
            die("shmat");

        t_counter = counter;

        int shmid;
        key_t key;

        struct listPid *tt, *lt;

        key = 1234;

        if ((shmid = shmget(key, sizeof(struct listPid), IPC_CREAT | 0666)) < 0)
            die("shmget");

        if ((tt = (struct listPid *)shmat(shmid, NULL, 0)) == (struct listPid *) -1)
            die("shmat");

        lt = tt;
        lt->child_pid[*t_counter] = p.getPid();
        lt->child_size[*t_counter] = p.array_size;
        sem_post(sem);
        p.task();

        return child;
    }
    else if(child > 0)
    {
        return child;
    }
    else
    {
        perror("couldn't fork()"); exit(1);
    }

}

int main()
{

    int a[2]; // Array storing list of pids

    int main_pid = getpid();

    // Semaphore to have mutex lock for counter
    sem_unlink("semname");
    sem_t * sem = sem_open ( "semname" , O_CREAT | O_EXCL , S_IRUSR | S_IWUSR , 0) ;
    if ( sem != SEM_FAILED )
        printf ( " created new semaphore !\n " ) ;
    else if ( errno == EEXIST )
    {
        sem = sem_open ( "semname" , 0) ;
    }
    int val =0;
    sem_post(sem);
    sem_getvalue ( sem , & val );
   // printf ( " semaphore ’s before action value is % d \n" , val ) ;

    int shmid;
    key_t counter_key;

    int *counter, *t_counter;

    counter_key = 1000;

    if ((shmid = shmget(counter_key, sizeof(int), IPC_CREAT | 0666)) < 0)
        die("shmget");

    if ((counter = (int *)shmat(shmid, NULL, 0)) == (int *) -1)
        die("shmat");

    t_counter = counter;
    *t_counter = -1;

    ProcessTableList plist;

    for(int i=0;i<2;i++)
    {
        sem_wait(sem);
        *t_counter += 1;
        a[i] = plist.addProcess();
    }
    if(main_pid == getpid()){
        int i=0;
        for(i=0;i<2;i++)
        {
            cout<<"Process: "<<a[i]<<"waiting to be scheduled"<<endl;
        }

        // Wait all the child process to get finished
        for (i = 0; i < 2; ++i) {
            int status;
            while (-1 == waitpid(a[i], &status, 0));
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                cerr << "Process " << i << " (pid " << a[i] << ") failed" << endl;
                exit(1);
            }
        }
    }

    return 0;
}