/* VarSet.cpp
 *
 */

#include <string>
#include <map>
#include <vector>
#include "VarSet.h"
#include "StringManip.h"
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
	Var rvar = Evaluate(st.target);

	if(!lvar) {
		//lvar didn't exist:
		if(st.op == "=") {
			SetVarAsString(st.subject, st.target);  //TODO:  evaluate string; should SetVarAsString do it?
		} else {
#if defined DEBUGEXTRA
			char msg[128];
			sprintf(msg, "VarSet::Command:  Misunderstood command:  \"%s\"", cmd.c_str());
			Logger(msg);
#endif //DEBUGEXTRA
		}
		return 0;
	} else {
	}
	/*
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
#if defined DEBUGEXTRA
			char msg[128];
			sprintf(msg, "VarSet::Command:  Type mismatch error in command:  \"%s\"", cmd.c_str());
			Logger(msg);
#endif //DEBUGEXTRA
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
	*/
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

Var VarSet::Evaluate(const string& cmd) {
	Var retval;
	return retval;
}


Var VarSet::EvaluateAsString(const string& cmd) {
	Var retval;
	// examples:  "this string is enclosed in quotes"         | this string is enclosed in quotes
	//            this string is not in quotes                | this string is not in quotes
	//            "part of this string" is not in quotes      | part of this string is not in quotes
	//            "this string" contains "uneven quotes       | (error; returns Var with dtype NONE)
	//            value: $data                                | value: 1
	//            "value:" $data                              | value: 1
	//            value: "$data"                              | value: $data
	// plan:      use a vector of Var*s, concatenate result
	if(cmd != "") {
		// search from left to right for \"
		/*
		size_t firstQuote = cmd.find("\"", 0);
		if(firstQuote != string::npos) {
			//found our first quote...  now look for its friend
			size_t nextQuote = cmd.find("\"", firstQuote);
		}
		*/
		std::vector<string::const_iterator> quotes;
		for(string::const_iterator i = cmd.begin(); i != cmd.end(); i++) {
			if(*i == '\"') quotes.push_back(i);
		}
		//if(quotes.count() %2 == 1) {
		//	//error, odd number of quotes detected
		//} else {
		//	// go left to right; text between quotes is unchanged, text outside quotes should be evaluated
		//}
	}
	return retval;
}
/*
Var VarSet::EvaluateAsInt(const string& cmd) {
	Var retval;
	return retval;
}

Var VarSet::EvaluateAsDouble(const string& cmd) {
	Var retval;
	return retval;
}
*/
void VarSet::Clear() {
	for(varitr i=_vars.begin(); i!=_vars.end(); i++) {
		delete i->second;
	}
	_vars.clear();
}

varitr VarSet::GetVarItr(const string& name) {
	return _vars.find(name);
}
