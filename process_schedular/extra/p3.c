#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define SHMSIZE 27

main()
{
 char c;
 int shmid;
 key_t key;
 char *shm, *s;

 /*
 * We'll name our shared memory segment.
 */
 key = 5678;

 /*
 * Create the segment.
 */
 if ((shmid = shmget(key, SHMSIZE, 0666)) < 0) {
 perror("shmget");
 exit(1);
 }

 /*
 * Now we attach the segment to our data space.
 */
 if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
 perror("shmat");
 exit(1);
 }


 *shm++='3';
 *shm++=' ';
 *shm++='m';
 *shm++='e';
 *shm++='m';
 *shm++='o';
 *shm++='r';
 *shm++='y';
 *shm = NULL;
 exit(0);
} 