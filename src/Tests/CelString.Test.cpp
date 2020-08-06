/* CelString.Test.cpp
 *
 */

#if defined DEBUG

#include <cstdio>
#include <cassert>
#include "CelString.h"
#include "Logger.h"

int CelString::Test() {
	CelString cs1("100,200,300,40,150,20");
	char msg[128];
	sprintf(msg, "CelString::Test:  x=%d,y=%d,w=%d,h=%d,cx=%d,cy=%d",
			cs1.x, cs1.y, cs1.w, cs1.h, cs1.cx, cs1.cy);
	Logger(msg);
	CelString cs2(",,,,,");
	CelString cs3("10,20,,40,20,10");
	CelString cs4("10,20,30.1,40,10,20");
	assert(cs1.isValid);
	assert(!cs2.isValid);
	assert(!cs3.isValid);
	assert(!cs4.isValid);
	sprintf(msg, "CelString::Test:  Tests passed!");
	Logger(msg);
	return 0;
}

#endif //DEBUG
