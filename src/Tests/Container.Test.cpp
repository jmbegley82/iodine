/* Container.Test.cpp
 *
 */

#if defined DEBUG
#include <cstdio>
#include "Container.h"
#include "Logger.h"
#include "Atom.h"

template class Container<int>;
template class Container<Atom>;

void cttestloop(Container<Atom>* ct) {
	char msg[128];
	for(int i=0; i<ct->GetCount(); i++) {
		sprintf(msg, "Container_Test:  index=%d, identity=%s", i, ct->GetByIndex(i)->GetIdentity().c_str());
		Logger(msg);
	}
	sprintf(msg, "Container_Test:  _count=%d, _countMax=%d", ct->GetCount(), ct->GetCountMax());
	Logger(msg);
}

int Container_Test() {
	//Container<int> cnt;
	//int test = 2;
	//cnt.Add("what", &test);
	
	Container<Atom> tester;
	Atom* a = new Atom("Test1");
	Atom* b = new Atom("Test2");
	Atom* c = new Atom("Test3");
	Atom* d = new Atom("Test4");
	Atom* e = new Atom("Test5");
	Atom* f = new Atom("Test6");
	tester.Add("Test1", a);
	tester.Add("Test2", b);
	tester.Add("Test3", c);
	cttestloop(&tester);
	tester.DestroyByName("Test2");
	cttestloop(&tester);
	
	tester.Add("Test5", e);
	cttestloop(&tester);
	tester.Shrink();
	cttestloop(&tester);
	tester.Add("Test4", d);
	cttestloop(&tester);
	tester.Add("Test6", f);
	cttestloop(&tester);

	tester.DestroyByName("Test1");
	tester.DestroyByName("Test3");
	tester.DestroyByName("Test5");
	cttestloop(&tester);

	//end section
	Logger("Container::Test:  attempting to DestroyAllAtoms()...");
	tester.DestroyAll();
	Logger("Container::Test:  success (presumed since this line printed)!");
	return 0;
}

#endif //DEBUG
