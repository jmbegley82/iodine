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
		Log(string("LList_Test:  numbers:  item #") + to_string(i) + " = " + to_string(numbers.GetByIndex(i)->item));
	}
	LList<int> subset = numbers.GetRange(numbers.GetByIndex(2), numbers.GetByIndex(5));
	//subset hopefully contains {3, 4, 5, 6}
	LList<int>::iterator itr = subset.GetFirst();
	int subcount = 0;
	while(itr != NULL) {
		Log(string("LList_Test:  subset:   item #") + to_string(subcount) + " = " + to_string(itr->item));
		itr = itr->next;
		++subcount;
	}
	return 0;
}

#endif //DEBUG
