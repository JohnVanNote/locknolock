/* noLock.c
 *
 * simulates people in a stadium getting up for food
 * practices threading without locks
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"

void *forfood(void* arg);

int main(void)
{
	const int ppl_n = 1000; /* the number of people in the stadium */
	pthread_t ppl[ppl_n]; /* people are threads */
	
	/* everyone gets up for food, 1000 times */
	int i;
	int count = 0;
	for(i=0; i<ppl_n; i++) {
		Pthread_create(&ppl[i], NULL, forfood, &count);
	}

	/* thread termination */
	for(i=0; i<ppl_n; i++) {
		Pthread_join(ppl[i], NULL);
	}
	
	/* or did they? */
	printf("The final count is %d\n", count);
	pthread_exit(0);

	return 0;
}

/* forfood: takes an arg iterates it 1000 times 
 * @param: arg is a void that will act like an int
 * return: nothing but arg will be iterated 1000 times (in theory)
 */
void *forfood(void* arg) {
	int i;
	int* count = (int*)arg;
	for(i=0; i<1000; i++) {
		(*count)++;
	}
	pthread_exit(0);
}
