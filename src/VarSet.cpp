/* VarSet.cpp
 *
 */

#include <string>
#include <map>
#include "VarSet.h"
#include "StringManip.h"

using std::string;
using std::map;

VarSet::VarSet() {
}

VarSet::~VarSet() {
	Clear();
}

int VarSet::Command(const string& cmd) {
	Sentence st(cmd);
	/* valid syntax:
	 * var = 1
	 * var = 1.0
	 * var = string of text
	 * delete var
	 */
	//declarator subject op target
	if(st.declarator == "delete") {
		DelVar(st.subject);
		return 0;
	}
	Var* lvar = GetVar(st.subject);
	Var rvar;
	rvar.SetValueAsString(st.target);
	if(!lvar) {
		SetVarAsString(st.subject, st.target);
		return 0;
	}
	if(lvar->IsValidNumericData()) {
		// it's a number!  += will add, -= will subtract, etc.
		double leftside = lvar->GetValueAsDouble();
		double rightside = rvar.GetValueAsDouble();
		if(!rvar.IsValidNumericData()) {
			// but this isn't useful numeric data
			return -1;
		}
		if(st.op == "=") {
			lvar->SetValueAsDouble(rightside);
			return 0;
		} else if(st.op == "+=") {
			lvar->SetValueAsDouble(leftside + rightside);
			return 0;
		} else if(st.op == "-=") {
			lvar->SetValueAsDouble(leftside - rightside);
			return 0;
		} else if(st.op == "*=") {
			lvar->SetValueAsDouble(leftside * rightside);
			return 0;
		} else if(st.op == "/=") {
			lvar->SetValueAsDouble(leftside / rightside);
			return 0;
		} else if(st.op == "^=") {
			//NI
			return -1;
		} else return -1;
	} else {
		// it's a string!  += will concatenate
		string leftside = lvar->GetValueAsString();
		string rightside = rvar.GetValueAsString();
		if(st.op == "=") {
			lvar->SetValueAsString(rightside);
			return 0;
		} else if(st.op == "+=") {
			lvar->SetValueAsString(leftside + rightside);
			return 0;
		} else return -1;
	}
	return CmdSink::Command(cmd);
}
/*
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
*/
/*
bool VarSet::CreateVar(const string& name, const string& val) {
	bool retval = false;
	return retval;
}
*/
void VarSet::SetVarAsString(const string& name, const string& val) {
	Var* var = GetVar(name);
	if(!var) {
		var = new Var();
		_vars.insert(varpair(name,var));
	}
	var->SetValueAsString(val);
}

void VarSet::SetVarAsInt(const string& name, int val) {
	Var* var = GetVar(name);
	if(!var) {
		var = new Var();
		_vars.insert(varpair(name,var));
	}
	var->SetValueAsInt(val);
}

void VarSet::SetVarAsDouble(const string& name, double val) {
	Var* var = GetVar(name);
	if(!var) {
		var = new Var();
		_vars.insert(varpair(name,var));
	}
	var->SetValueAsDouble(val);
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
	for(varitr i=_vars.begin(); i!=_vars.end(); i++) {
		delete i->second;
	}
	_vars.clear();
}

varitr VarSet::GetVarItr(const string& name) {
	return _vars.find(name);
}
