#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
/* function prototypes */
void die(const char*);
 
int main(int argc, char **argv) {
	int pdes[2],c;
	pid_t child;
 
	if(pipe(pdes) == -1)
		die("pipe()");
 
	child = fork();
	if(child == (pid_t)(-1))
        	die("fork()"); /* fork failed */
 
	if(child == (pid_t)0) {
        	/* child process */
 
        	close(1);       /* close stdout */
 
        	if(dup(pdes[1]) == -1)
        		die("dup()");
 
        	/* now stdout and pdes[1] are equivalent (dup returns lowest free descriptor) */
               c =  execlp("program1", "program1", "arg1", NULL);
        	if(c == -1)
        		die("execlp()");
 
		_exit(EXIT_SUCCESS);
	} else {
        	/* parent process */
 
        	close(0);       /* close stdin */
 
        	if(dup(pdes[0]) == -1)
        		die("dup()");
 
        	/* now stdin and pdes[0] are equivalent (dup returns lowest free descriptor) */
                c = execlp("program2", "program2", "arg1", NULL);
        	if( c == -1)
        		die("execlp()");
 
		exit(EXIT_SUCCESS);
	}
 
	return 0;
}
 
void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}