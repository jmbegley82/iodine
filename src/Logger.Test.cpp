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
	Log(msg + "The test where you pass an absurdly long string from the C++ part of Logger to the C part of Logger and "
		+ "hope like hell that it chunks it up correctly and doesn't SEGFAULT and doesn't access invalid memory at "
		+ "0xWherever, and also doesn't raid your address book and email client and sell the data to yada yada yada "
		+ "etc. passed!");
	Log_now(msg + "Log_now test passed!");
	return 0;
}

#endif //DEBUG
