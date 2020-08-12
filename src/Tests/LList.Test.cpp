/* LList.Test.cpp
 *
 */

#if defined DEBUG

#include "LList.h"
#include "Atom.h"
#include "Logger.h"

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
	test.Remove(test.Get(3));
	test.Remove(test.GetFirst());
	LList<Atom*>::iterator i = test.GetFirst();
	while(i != NULL) {
		Log(string("LList_Test:  i->item->identity = ") + i->item->GetIdentity());
		i = i->next;
	}
	Log(string("LList_Test:  test.GetCount() = ") + std::to_string(test.GetCount()));

	LList<Atom*>::iterator j = test.GetFirst();
	Log(string("LList_Test:  j->item->identity = ") + j->item->GetIdentity());
	LList<Atom*>::iterator k = test.GetLast();
	Log(string("LList_Test:  k->item->identity = ") + k->item->GetIdentity());
	/*
	i = test.GetFirst();
	while(i != NULL) {
		delete i->item;
		test.Remove(i);
		i = i->next;
		Log(string("LList_Test:  test.GetCount() = ") + std::to_string(test.GetCount()));
	}
	*/
	test.Clear();
	Log(string("LList_Test:  test.GetCount() = ") + std::to_string(test.GetCount()));
	return 0;
}

#endif //DEBUG
