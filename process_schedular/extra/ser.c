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

 /* * We'll name our shared memory segment * "5678". */

 key = 5678;

 /* * create the segment.* */

 shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)
 

 /** Now we attach the segment to our data space.*/

 shm = shmat(shmid, NULL, 0); 

 /** Now put some things into the memory for the other process to read. */
  s = shm;

 for (c = 'a'; c <= 'z'; c++)
 *s++ = c;
 *s = NULL;

 /** Finally, we wait until the other process
 * Changes the first character of our memory
 * to '*', indicating that it has read what
 * we put there.
 */
 while (*shm != '*')
 sleep(1);

 exit(0);
} 