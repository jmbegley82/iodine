/* LList.Test.cpp
 *
 */

#if defined DEBUG

#include <string>
#include "LList.h"
#include "Logger.h"

using std::string;
using std::to_string;

#define TESTCOUNT 15

int LList_Test() {
	LList<int> numbers;
	for(int i=1; i<=TESTCOUNT; ++i) {
		numbers.Add(i);
	}
	for(int i=0; i<TESTCOUNT; ++i) {
		Log(string("LList_Test:  item #") + to_string(i) + " = " + to_string(numbers.GetByIndex(i)->item));
	}
	return 0;
}

#endif //DEBUG
