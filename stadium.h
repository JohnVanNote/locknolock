/* stadium.h -- header file */
#ifndef _STADIUM_H_
#define _STADIUM_H_

#include <pthread.h>


/* check file 'stadium.c' for proper function descriptions */
void *forfood(void* argc);
void *forfoodlockin(void* argc);
void *forfoodlockout(void* argc);
int noLock(int ppl_n);
int lockIn(int ppl_n);
int lockOut(int ppl_n);

#endif
/* ends stadium.h */

