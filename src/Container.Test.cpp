/* Container.Test.cpp
 *
 */

#if defined DEBUG

#include <cstdio>
#include "Container.h"
#include "Atom.h"
#include "Logger.h"

void cttestloop(Container* ct) {
	char msg[128];
	for(int i=0; i<ct->GetCount(); i++) {
		sprintf(msg, "Container::Test:  index=%d, identity=%s", i, ct->GetAtomByIndex(i)->GetIdentity().c_str());
		Logger(msg);
	}
	sprintf(msg, "Container::Test:  _count=%d, _countMax=%d", ct->GetCount(), ct->GetCountMax());
	Logger(msg);
}

int Container::Test() {
	Container tester;
	Atom* a = new Atom("Test1");
	Atom* b = new Atom("Test2");
	Atom* c = new Atom("Test3");
	Atom* d = new Atom("Test4");
	Atom* e = new Atom("Test5");
	Atom* f = new Atom("Test6");
	tester.AddAtom(a);
	tester.AddAtom(b);
	tester.AddAtom(c);
	cttestloop(&tester);
	tester.DestroyAtomByName("Test2");
	cttestloop(&tester);
	
	tester.AddAtom(e);
	cttestloop(&tester);
	tester.Shrink();
	cttestloop(&tester);
	tester.AddAtom(d);
	cttestloop(&tester);
	tester.AddAtom(f);
	cttestloop(&tester);

	//end section
	Logger("Container::Test:  attempting to DestroyAllAtoms()...");
	tester.DestroyAllAtoms();
	Logger("Container::Test:  success (presumed since this line printed)!");
	return 0;
}

#endif //DEBUG
