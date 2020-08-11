/* LList.Test.cpp
 *
 */

#if defined DEBUG

#include "LList.h"
#include "Atom.h"

int LList_Test() {
	LList<Atom*> test;
	Atom* a1 = new Atom("a1");
	Atom* a2 = new Atom("a2");
	Atom* a3 = new Atom("a3");
	Atom* a4 = new Atom("a4");
	Atom* a5 = new Atom("a5");
	Atom* a6 = new Atom("a6");
	test.Add(a1);
	test.Add(a2);
	test.Add(a3);
	test.Add(a4);
	test.Add(a5);
	test.Add(a6);
	LLitem<Atom*>* i = test.Get(0);
	Log(string("LList_Test:  i->item->identity = ") + i->item->GetIdentity());
	return 0;
}

#endif //DEBUG
