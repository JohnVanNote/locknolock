#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "stadium.h"

int main(int argc, char *argv[]) {

	int i; /* iterator */
	int trials = 10; /* number of times the functions will be run */
	int ppl_n = 1000; /* the number of people "in the stadium */
	int avgcount = 0; /* the average count */
	clock_t time = clock(); /* function timing */

	/* getting up for food without a mutex */
	if(strcmp(argv[1], "1") == 0) {
		for(i=0; i<trials; i++)
			avgcount = avgcount + noLock(ppl_n);
	}

	/* getting up for food with a mutex inside the loop */
	else if(strcmp(argv[1], "2") == 0) {
		for(i=0; i<trials; i++)
			avgcount = avgcount + lockIn(ppl_n);
	}

	/* getting up for food with a mutex out of the loop */
	else if (strcmp(argv[1], "3") == 0) {
		for(i=0; i<trials; i++)
			avgcount = avgcount + lockOut(ppl_n);
	}

	/* something fucked up */
	else {
		perror("Invalid argument");
		perror("I find your lack of faith disturbing...");
		exit(0);
	}

	avgcount = avgcount/trials; /* final average */
	time = clock() - time; /* final time */
	printf("The avg count is %d out of 1,000,000\n",
			avgcount);
	printf("It took %f seconds to calculate\n", 
			(((float)time)/CLOCKS_PER_SEC));
	pthread_exit(0);
	return 0;
}
