/* inLoopLock.c
 *
 * simulates people in a stadium getting up for food
 * practices threading with mutex outside for-loop
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"

/* globals for mutex and condition */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *forfood(void* arg);

int main(void)
{
	const int ppl_n = 1000; /* the number of people in the stadium */
	pthread_t ppl[ppl_n]; /* people are threads */
	
	int i;
	int count = 0;
	/* everyone gets up for food, 1000 times */
	for(i=0; i<ppl_n; i++) {
		Pthread_create(&ppl[i], NULL, forfood, &count);
	}

	/* thread termination */	
	for(i=0; i<ppl_n; i++) {
		Pthread_join(ppl[i], NULL);
	}

	/* should be 100,000 */
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
	pthread_mutex_lock(&mutex);
	for(i=0; i<1000; i++) {
		(*count)++;
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}
