#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

/* Read characters from the pipe and echo themvoid*/
void read_from_pipe (int file)
{
    FILE *stream;
    int c;
    stream = fdopen (file, "r");
    while ((c = fgetc (stream)) != EOF)p
    putchar (c);
    fclose (stream);
}
/* Write some random text to the pipe. */
void write_to_pipe (int file)
{
    FILE *stream;
    stream = fdopen (file, "w");
    fprintf (stream, "hello, world!\n");
    fprintf (stream, "goodbye, world!\n");
    fclose (stream);
}
int main ()
{
    pid_t pid;
    int mypipe[2];
   // printf("%d",pid);
    /* Create the pipe. */
    if (pipe (mypipe))
    {
        printf("if---1");
        fprintf (stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
    /* Create the child process. */
    /* On success, fork() returns 0 to the child process and returns the process ID of the child process to
    the parent process. On failure, fork() returns -1
    to the parent process, sets errno to indicate the error, and no child process is created.  */
    pid = fork ();
    printf("%d",pid);
    if (pid == (pid_t) 0) // converting 0 to a process id data type
    {
        printf("if---2\n");
        /* This is the child process.Close other end first. */
        close (mypipe[1]);
        read_from_pipe (mypipe[0]);
        return EXIT_SUCCESS;
    }
    else if (pid < (pid_t) 0)
    {
        printf("if---else if\n");
        /* The fork failed. */
        fprintf (stderr, "Fork failed.\n");
        return EXIT_FAILURE;
    }
    else
    {
        printf("---else\n");
        /* This is the parent process.Close other end first. */
        close (mypipe[0]);
        write_to_pipe (mypipe[1]);
        return EXIT_SUCCESS;
    }
}
