/* VarSet.Test.cpp
 *
 */

#if defined DEBUG

#include <cstdio>
#include "VarSet.h"
#include "Var.h"
#include "Logger.h"

void vsdetail(const char* name, Var* var) {
	char msg[128];
	if(!var) {
		sprintf(msg, "VarSet::Test:  vsdetail:  %s is null!", name);
	} else {
		sprintf(msg, "VarSet::Test:  vsdetail:  %s->GVAI=%d, %s->GVAD=%16f, %s->GVAS=%s", name, var->GetValueAsInt(),
			name, var->GetValueAsDouble(), name, var->GetValueAsString().c_str());
	}
	Logger(msg);
}

int VarSet::Test() {
	VarSet* vs = new VarSet();
	/*
	Var* a = new Var();
	Var* b = new Var();
	Var* c = new Var();
	a->SetValueAsInt(1);
	b->SetValueAsInt(2);
	c->SetValueAsInt(3);
	vs->AddVar("a", a);
	vs->AddVar("b", b);
	vs->AddVar("c", c);
	vsdetail("a", vs->GetVar("a"));
	vsdetail("b", vs->GetVar("b"));
	vsdetail("c", vs->GetVar("c"));
	vs->Clear();
	vsdetail("c", vs->GetVar("c"));
	delete a;
	delete b;
	delete c;
	*/
	vs->SetVarAsString("a", "1");
	vs->SetVarAsString("b", "2");
	vs->SetVarAsString("c", "3");
	vsdetail("a", vs->GetVar("a"));
	vsdetail("b", vs->GetVar("b"));
	vsdetail("c", vs->GetVar("c"));
	vs->SetVarAsInt("c", 4);
	vsdetail("c", vs->GetVar("c"));
	vs->Clear();
	delete vs;
	return 0;
}

#endif //DEBUG
