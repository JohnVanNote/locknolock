#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csapp.h"

/* globals for mutex and condition */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *forfood(void* argc);
void *forfoodlockin(void* argc);
void *forfoodlockout(void* argc);
int noLock(int ppl_n);
int lockIn(int ppl_n);
int lockOut(int ppl_n);

int main(int argc, char *argv[]) {

	int i;
	int trials = 10;
	int ppl_n = 1000;
	int avgcount = 0;

	if(strcmp(argv[1], "1") == 0) {
		for(i=0; i<trials; i++)
			avgcount = avgcount + noLock(ppl_n);
	}
	else if(strcmp(argv[1], "2") == 0) {
		for(i=0; i<trials; i++)
			avgcount = avgcount + lockIn(ppl_n);
	}
	else if (strcmp(argv[1], "3") == 0) {
		for(i=0; i<trials; i++)
			avgcount = avgcount + lockOut(ppl_n);
	}
	else {
		perror("Invalid argument");
		perror("I find your lack of faith distrubing...");
		exit(0);
	}

	avgcount = avgcount/10;
	printf("The avg count is %d out of 1,000,000\n", avgcount);
	pthread_exit(0);
	return 0;
}

/* forfood: takes an arg iterates it 1000 times 
 * @param arg: is a void that will act like an int
 * no return: arg will be iterated 1000 times (in theory)
 */
void *forfood(void* arg) {
	int i;
	int* count = (int*)arg;
	for(i=0; i<1000; i++) {
		(*count)++;
	}
	pthread_exit(0);
	return;
}

/* forfoodlockin: takes arg iterates it 1000 times with mutex in loop
 * @param arg: a void that will act like an int
 * no return: arg will be iterated 1000 times
 */
void *forfoodlockin(void* arg) {
	int i;
	int* count = (int*)arg;
	for(i=0; i<1000; i++) {
		pthread_mutex_lock(&mutex);
		(*count)++;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
	return;
}

/* forfoodlockout: takes arg iterates 1000 times with mutex out of loop
 * @param arg: a void that will act like an int
 * no return: arg will be iterated 1000 times
 */
void *forfoodlockout(void* arg) {
	int i;
	int* count = (int*)arg;
	pthread_mutex_lock(&mutex);
	for(i=0; i<1000; i++) {
		(*count)++;
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
	return;
}

/* noLock: runs forfood and gets count
 * @param ppl_n: number of people
 * @return: the turnstile count
 */
int noLock(int ppl_n) {
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
	return count;
}

/* lockIn: runs forfoodlockin and gets count
 * @param ppl_n: number of people
 * @return: the turnstile count
 */
int lockIn(int ppl_n) {
	pthread_t ppl[ppl_n]; /* people are threads */

	/* everyone gets up for food, 1000 times */
	int i;
	int count = 0;
	for(i=0; i<ppl_n; i++) {
		Pthread_create(&ppl[i], NULL, forfoodlockin, &count);
	}

	/* thread termination */
	for(i=0; i<ppl_n; i++) {
		Pthread_join(ppl[i], NULL);
	}

	/* should be 1,000,000 */
	return count;
}

/* lockOut: runs forfoodlockout and gets count
 * @param ppl_n: number of people
 * @return: the turnstile count
 */
int lockOut(int ppl_n) {
	pthread_t ppl[ppl_n]; /* people are threads */

	/* everyone gets up for food, 1000 times */
	int i;
	int count = 0;
	for(i=0; i<ppl_n; i++) {
		Pthread_create(&ppl[i], NULL, forfoodlockout, &count);
	}

	/* thread termination */
	for(i=0; i<ppl_n; i++) {
		Pthread_join(ppl[i], NULL);
	}

	/* should be 1,000,000 */
	return count;
}
