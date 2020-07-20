/* VarSet.cpp
 *
 */

#include <string>
#include <map>
#include <vector>
#include "VarSet.h"
#include "StringManip.h"
#include "Sentence.h"
#if defined DEBUGEXTRA
#include "Logger.h"
#endif //DEBUGEXTRA

using std::string;
using std::map;

VarSet::VarSet() {
}

VarSet::~VarSet() {
	Clear();
}

int VarSet::VSCommand(const string& cmd) {
	Sentence st(cmd);
	/* valid syntax:
	 * var = 1
	 * var = 1.0
	 * var = "string of text"
	 * var = $stuff
	 * delete var
	 */
	//declarator subject op target
	if(st.declarator == "delete") {
		DelVar(st.subject);
		return 0;
	}
	Var* lvar = GetVar(st.subject);
	Var rvar = Evaluate(st.target);

	if(!lvar) {
		//lvar didn't exist:
		if(st.op == "=") {
			Var* var = new Var();
			var->CopyValue(&rvar);
			_vars.insert(varpair(st.subject,var));
		} else {
#if defined DEBUGEXTRA
			char msg[128];
			sprintf(msg, "VarSet::VSCommand:  Misunderstood command:  \"%s\"", cmd.c_str());
			Logger(msg);
#endif //DEBUGEXTRA
		}
		return 0;
	} else {
		if(lvar->IsValidNumericData() && rvar.IsValidNumericData()) {
			// lvar is more of a number
			double left = lvar->GetValueAsDouble();
			double right = rvar.GetValueAsDouble();
			if(st.op == "=") {
				lvar->SetValueAsDouble(right);
			} else if(st.op == "+=") {
				left += right;
				lvar->SetValueAsDouble(left);
			} else if(st.op == "-=") {
				left -= right;
				lvar->SetValueAsDouble(left);
			} else if(st.op == "*=") {
				left = left * right;
				lvar->SetValueAsDouble(left);
			} else if(st.op == "/=") {
				left = left / right;
				lvar->SetValueAsDouble(left);
			} else if(st.op == "^=") {
				//NI
			} else {
#if defined DEBUGEXTRA
			char msg[128];
			sprintf(msg, "VarSet::VSCommand:  Misunderstood command:  \"%s\"", cmd.c_str());
			Logger(msg);
#endif //DEBUGEXTRA
			}
		} else {
			// lvar is more of a string
			if(st.op == "=") {
				lvar->CopyValue(&rvar);
			} else if(st.op == "+=") {
				string left = lvar->GetValueAsString();
				string right = rvar.GetValueAsString();
				//left += right;
				const string okfine = left + right;
				lvar->SetValueAsString(okfine);  //TODO: investigate error caused here
			} else {
#if defined DEBUGEXTRA
			char msg[128];
			sprintf(msg, "VarSet::VSCommand:  Misunderstood command:  \"%s\"", cmd.c_str());
			Logger(msg);
#endif //DEBUGEXTRA
			}
		}
		return 0;
	}
	return -9000;
	//return CmdSink::Command(cmd);
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

Var VarSet::Evaluate(const string& cmd) {
	// assume leading/trailing spaces have been stripped
	Var retval;
	retval.SetValueAsString("");
	if(cmd == "") {
		// let's just go ahead and get that out of the way
	} else if(cmd[0] == '#' || cmd[0] == '$') {
		// this refers to the numeric/string value of a variable
		string::const_iterator i = cmd.begin() + 1;
		string sub = string(i, cmd.end());
		Var* lookup = GetVar(sub);
		if(lookup) {
			// we found one!
			retval.CopyValue(lookup);
		} else {
			// Var not found
		}
	} else if(cmd[0] == '\"') {
		// this refers to a string literal value (ideally there is a closing quote which terminates it)
		string sub = DeQuote(cmd);
		retval.SetValueAsString(sub);
	} else {
		// at this point the only thing left is a numeric literal value, so check it thoroughly!
		if(ContainsNumericData(cmd)) {
			// looks numeric to me
			retval.SetValueAsString(cmd);
		}
	}
	//retval.SetValueAsString(cmd);
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
