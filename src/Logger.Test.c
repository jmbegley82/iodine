/* Logger.Test.c
 *
 */

#if defined DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Logger.h"

void* Logger_Test_Thread(void *arg) {
	int reps = 100000;  // set to # of desired iterations
	for(int i=0; i<reps; i++) {
		char msg[128] = {};
		sprintf(msg, "Logger_Test:  Thread#%05ld:  Bombardment#%05d", (long int)arg, i);
		int r = rand() %200;
		if(r == 30) {
			// randomly resize the logbuffer because pain is fun
			Logger_setmaxlines(rand()%1000 + 2);
		} else if(r == 40) {
			// randomly change logbuffer line length because chaos is also fun
			Logger_setmaxlinelength(rand()%122+10);
		}
		Logger(msg);
	}
	pthread_exit((void*)0);
}

int Logger_Test() {
	int threadcount = 7;  // set to # of desired concurrent testing threads
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_t threads[threadcount];
	for(int i=0; i<threadcount; i++) {
		pthread_create(&threads[i], &attr, Logger_Test_Thread, (void*)(long int)i);
	}
	pthread_attr_destroy(&attr);
	// wait for threads to end
	void* status;
	for(int i=0; i<threadcount; i++) {
		pthread_join(threads[i], &status);
	}
	Logger_setmaxlinelength(80);
	Logger_setmaxlines(128);
	return 0;
}
#endif //DEBUG
