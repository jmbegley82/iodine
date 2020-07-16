/* VarSet.Test.cpp
 *
 */

#if defined DEBUG

#include <cstdio>
#include "VarSet.h"
#include "Var.h"
#include "Logger.h"

void vstcmd(VarSet* vs, const string& cmd) {
	char msg[128];
	sprintf(msg, "VarSet::Test:  vstcmd(%s)", cmd.c_str());
	Logger(msg);
	vs->Command(cmd);
}

void vstdetail(VarSet* vs, const string& name) {
	char msg[128];
	const char* cname = name.c_str();
	Var* var = vs->GetVar(name);
	if(!var) {
		sprintf(msg, "VarSet::Test:  vstdetail:  %s is null!", cname);
	} else {
		sprintf(msg, "VarSet::Test:  vstdetail:  %s->GVAI=%d, %s->GVAD=%16f, %s->GVAS=%s", cname, var->GetValueAsInt(),
			cname, var->GetValueAsDouble(), cname, var->GetValueAsString().c_str());
	}
	Logger(msg);
}

int VarSet::Test() {
	VarSet* vs = new VarSet();
	/*
	vs->SetVarAsString("a", "1");
	vs->SetVarAsString("b", "2");
	vs->SetVarAsString("c", "3");
	vstdetail(vs, "a");
	vstdetail(vs, "b");
	vstdetail(vs, "c");
	*/
	//vs->SetVarAsInt("c", 4);
	vstcmd(vs, "c = 4");
	vstdetail(vs, "c");
	vstcmd(vs,"c+=3");
	vstdetail(vs, "c");
	vstcmd(vs,"c=\"Lol here have a string.\"");
	vstdetail(vs, "c");
	vstcmd(vs,"c+=\"Let's add an additional string to it!\"");
	vstdetail(vs, "c");
	vstcmd(vs,"c+=9");
	vstdetail(vs, "c");
	vs->Clear();
	vstcmd(vs,"d=\"\"");
	vstdetail(vs, "d");
	vstcmd(vs,"d+=\"string!\"");
	vstdetail(vs, "d");
	vstcmd(vs,"d+=\" an additional string!!\"");
	vstdetail(vs, "d");
	vstcmd(vs,"d=\"just one string now\"");
	vstdetail(vs, "d");
	vstcmd(vs,"d=\"\"");
	vstdetail(vs, "d");
	vs->Clear();
	vstcmd(vs, "data=3.14159");
	vstcmd(vs, "msg=\"The value stored in data is \"");
	vstcmd(vs, "msg+=#data");
	vstdetail(vs, "data");
	vstdetail(vs, "msg");
	delete vs;
	return 0;
}

#endif //DEBUG
