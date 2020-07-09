/* Timing.Test.c
 *
 */

#if defined DEBUG
#include <stdio.h>
#include "Timing.h"
#include "Logger.h"

int Timing_Test() {
	char msg[128] = {};
	Logger_pause();
	Logger_now("There should be one second between the next few lines that are printed.");
	SleepMsec(1000);
	sprintf(msg, "GetTimeInMsec: %f", GetTimeInMsec());
	Logger_now(msg);
	SleepMsec(1000);
	sprintf(msg, "GetTimeInMsec: %f", GetTimeInMsec());
	Logger_now(msg);
	SleepUsec(1000000);
	sprintf(msg, "GetTimeInMsec: %f", GetTimeInMsec());
	Logger_now(msg);
	SleepMsec(1000);
	sprintf(msg, "GetTimeInMsec: %f", GetTimeInMsec());
	Logger_now(msg);
	SleepUsec(1000000);
	sprintf(msg, "GetTimeInMsec: %f", GetTimeInMsec());
	Logger_now(msg);
	SleepMsec(1000);
	sprintf(msg, "GetTimeInMsec: %f", GetTimeInMsec());
	Logger_now(msg);
	sprintf(msg, "GetTimeInUsec: %f", GetTimeInUsec());
	Logger_now(msg);
	Logger_unpause();
}
#endif //DEBUG
