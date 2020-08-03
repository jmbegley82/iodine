/* Container.Test.cpp
 *
 */

#if defined DEBUG
#include "Container.h"
#include "Logger.h"
#include "Atom.h"

template class Container<int>;

int Container_Test() {
	Container<int> cnt;
	//Atom* atm = new Atom("test");
	int test = 2;
	cnt.Add("what", &test);
	return 0;
}

#endif //DEBUG
