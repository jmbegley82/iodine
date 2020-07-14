/* VarSet.cpp
 *
 */

#include <string>
#include <map>
#include "VarSet.h"

using std::string;
using std::map;

VarSet::VarSet() {
}

VarSet::~VarSet() {
	Clear();
}

int VarSet::Command(const string& cmd) {
	//NI
	return CmdSink::Command(cmd);
}

bool VarSet::AddVar(const string& name, Var* var) {
	bool retval = false;
	if(!GetVar(name)) {
		_vars.insert(varpair(name,var));
		retval = true;
	}
	return retval;
}

void VarSet::AddVar_forced(const string& name, Var* var) {
	if(GetVar(name)) DelVar(name);
	_vars.insert(varpair(name,var));
}

bool VarSet::DelVar(const string& name) {
	bool retval = false;
	varitr it = GetVarItr(name);
	if(it != _vars.end()) {
		_vars.erase(it);
		retval = true;
	}
	return retval;
}

Var* VarSet::GetVar(const string& name) {
	Var* retval = NULL;
	varitr it = GetVarItr(name);
	if(it != _vars.end()) retval = it->second;
	return retval;
}

string VarSet::GetVarAsString(const string& name) {
	string retval = "(missing)";
	Var* var = GetVar(name);
	if(var) retval = var->GetValueAsString();
	return retval;
}

int VarSet::GetVarAsInt(const string& name) {
	int retval = 0;
	Var* var = GetVar(name);
	if(var) retval = var->GetValueAsInt();
	return retval;
}

double VarSet::GetVarAsDouble(const string& name) {
	double retval = 0.0;
	Var* var = GetVar(name);
	if(var) retval = var->GetValueAsDouble();
	return retval;
}

void VarSet::Clear() {
	_vars.clear();
}

varitr VarSet::GetVarItr(const string& name) {
	return _vars.find(name);
}
