/* Timing.c
 *
 */

#include <unistd.h>
#include <time.h>
#include "Timing.h"

double GetTimeInMsec() {
	double retval = 0;
	//almost-certainly-linux-specific code follows
	struct timespec currentTime;
	clock_gettime(CLOCK_MONOTONIC_RAW, &currentTime);
	retval = currentTime.tv_sec * 1000.0;
	retval += currentTime.tv_nsec / 1000000.0;
	return retval;
}

double GetTimeInUsec() {
	double retval = 0;
	//almost-certainly-linux-specific code follows
	struct timespec currentTime;
	clock_gettime(CLOCK_MONOTONIC_RAW, &currentTime);
	retval = currentTime.tv_sec * 1000000.0;
	retval += currentTime.tv_nsec / 1000.0;
	return retval;
}

void SleepMsec(double ms) {
	if(ms > 0) usleep((int)(ms*1000.0));
}

void SleepUsec(int us) {
	if(us > 0) usleep(us);
}
