/* Logger.Test.cpp
 *
 */

#if defined DEBUG

#include <string>
#include "Logger.h"

using std::string;

int LogCxxTest() {
	string msg = "LogCxxTest:  ";
	Log(msg + "Log test passed!");
	Log_now(msg + "Log_now test passed!");
	return 0;
}

#endif //DEBUG
