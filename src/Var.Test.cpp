/* Var.Test.cpp
 *
 */

#if defined DEBUG

#include <cstdio>
#include "Var.h"
#include "Logger.h"

void vdetail(const char* name, Var* var) {
	char msg[128];
	sprintf(msg, "Var::Test:  vdetail:  %s->GVAI=%d, %s->GVAD=%16f, %s->GVAS=%s", name, var->GetValueAsInt(), name,
		var->GetValueAsDouble(), name, var->GetValueAsString().c_str());
	Logger(msg);
}

int Var::Test() {
	Var* a = new Var();
	Var* b = new Var();
	Var* c = new Var();
	a->SetValueAsString("1");
	b->SetValueAsInt(2);
	c->SetValueAsDouble(3);
	vdetail("a", a);
	vdetail("b", b);
	vdetail("c", c);
	delete a;
	delete b;
	delete c;
	Var* d = new Var();
	d->SetValueAsDouble(4.0);
	d->Clear();
	vdetail("d", d);
	delete d;
	return 0;
}

#endif //DEBUG
