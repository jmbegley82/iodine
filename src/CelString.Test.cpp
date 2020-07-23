/* CelString.Test.cpp
 *
 */

#if defined DEBUG

#include <cstdio>
#include "CelString.h"
#include "Logger.h"

int CelString::Test() {
	CelString cs1("100,200,300,40");
	char msg[128];
	sprintf(msg, "CelString::Test:  x=%d,y=%d,w=%d,h=%d", cs1.x, cs1.y, cs1.w, cs1.h);
	Logger(msg);
	return 0;
}

#endif //DEBUG
