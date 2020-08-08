/* Array.Test.cpp
 *
 */

#if defined DEBUG
#include <cstdio>
#include "Array.h"
#include "Logger.h"
#include "Atom.h"

//template class Array<int>;
//template class Array<Atom>;

void cttestloop(Array<Atom>* ct) {
	char msg[128];
	for(int i=0; i<ct->GetCount(); i++) {
		sprintf(msg, "Array_Test:  index=%d, identity=%s", i, "");
		Logger(msg);
	}
	sprintf(msg, "Array_Test:  _count=%d, _countMax=%d", ct->GetCount(), ct->GetCountMax());
	Logger(msg);
}

int Array_Test() {
	//Array<int> cnt;
	//int test = 2;
	//cnt.Add("what", &test);
	
	Array<Atom> tester;
	Atom* a = new Atom("Test1");
	Atom* b = new Atom("Test2");
	Atom* c = new Atom("Test3");
	Atom* d = new Atom("Test4");
	Atom* e = new Atom("Test5");
	Atom* f = new Atom("Test6");
	tester.Add(a);
	tester.Add(b);
	tester.Add(c);
	cttestloop(&tester);
	//tester.DestroyByName("Test2");
	cttestloop(&tester);
	
	tester.Add(e);
	cttestloop(&tester);
	tester.Shrink();
	cttestloop(&tester);
	tester.Add(d);
	cttestloop(&tester);
	tester.Add(f);
	cttestloop(&tester);

	//tester.DestroyByName("Test1");
	//tester.DestroyByName("Test3");
	//tester.DestroyByName("Test5");
	cttestloop(&tester);

	//end section
	Logger("Array::Test:  attempting to Clear()...");
	tester.Clear();
	//delete a;
	//delete b;
	//delete c;
	//delete d;
	//delete e;
	//delete f;
	Logger("Array::Test:  success (presumed since this line printed)!");
	return 0;
}

#endif //DEBUG
