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
		sprintf(msg, "VarSet::Test:      vstdetail:  %s is null!", cname);
	} else {
		int varint = var->GetValueAsInt();
		double vardub = var->GetValueAsDouble();
		string varstr = var->GetValueAsString();
		const char* varcstr = varstr.c_str();
		sprintf(msg, "VarSet::Test:      vstdetail:  %s->GVAI=%d, %s->GVAD=%16f, %s->GVAS=%s", cname, varint,
			cname, vardub, cname, varcstr);
	}
	Logger(msg);
}

int VarSet::Test() {
	VarSet* vs = new VarSet();
	vstcmd(vs, "c = 4");
	vstdetail(vs, "c");
	vstcmd(vs,"c+=3");
	vstdetail(vs, "c");
	vstcmd(vs,"c=\"Here have a string.\"");
	vstdetail(vs, "c");
	vstcmd(vs,"c+=\"Add another string to it!\"");
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
	vs->Clear();
	vstcmd(vs, "msg=1");
	vstdetail(vs, "msg");
	vstcmd(vs, "msg+=\" is the loneliest number etc etc.\"");
	vstdetail(vs, "msg");
	vstcmd(vs, "msg=\"\"");
	vstdetail(vs, "msg");
	vstcmd(vs, "data=1.21");
	vstdetail(vs, "data");
	vstcmd(vs, "msg=\"This sentence contains $data, not 1.21\"");
	vstdetail(vs, "msg");
	vstcmd(vs, "msg=\"This sentence contains \"");
	vstcmd(vs, "msg+=$data");
	vstdetail(vs, "msg");
	vstcmd(vs, "msg=$msg");
	vstdetail(vs, "msg");
	vstcmd(vs, "msg=Error condition!");
	vstdetail(vs, "msg");
	vstcmd(vs, "msg+=1");
	vstdetail(vs, "msg");
	delete vs;
	return 0;
}

#endif //DEBUG
