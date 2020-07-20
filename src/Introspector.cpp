/* Introspector.cpp
 *
 */

#include <string>
#include <cmath>
#include "Introspector.h"
#include "IntReference.h"
#include "DoubleReference.h"
#include "StringManip.h"
#include "Sentence.h"

Introspector::Introspector() {
}

Introspector::~Introspector() {
	Clear();
}

int Introspector::ISCommand(const string& cmd) {
	Sentence st(cmd);
	/* valid syntax:
	 * var = 1
	 * var = 1.0
	 * var = #othervar
	 */

	//declarator subject op target
	if(st.declarator == "delete") {
		//DelVar(st.subject);
		return -1;  //NI
	}

	//by this point, any other non-empty declarator will be an error condition
	if(st.declarator != "") {
		return -1;
	}

	if(st.subject == "" || st.op == "" || st.target == "") {
		return -1;  // none of those things should be empty!
	}

	Reference* lref = GetRef(st.subject);
	double lval = 0.0;
	double rval = 0.0;

	if(!lref) {
		//lref didn't exist:
		return -1;
	} else lval = lref->GetValueAsDouble();

	if(*st.target.begin() == '#' && st.target.length() > 1) {
		// st.target begins with a #, signifying the name of another reference
		string target = string(st.target.begin()+1, st.target.end());
		Reference* rref = GetRef(target);
		if(!rref) {
			// named target did not exist in _refs!
			return -1;
		} else {
			rval = rref->GetValueAsDouble();
			//continue onward...
		}
	} else {
		// st.target needs to be checked for valid numeric data
		if(!ContainsNumericData(st.target)) {
			// that's not a number...
			return -1;
		} else {
			rval = std::stod(st.target);
		}
	}
	// at this point, lref and rval should be filled in and error conditions should have been caught
	// (except ones in st.op)

	if(st.op == "=") {
		lval = rval;
	} else if(st.op == "+=") {
		lval += rval;
	} else if(st.op == "-=") {
		lval -= rval;
	} else if(st.op == "*=") {
		lval *= rval;
	} else if(st.op == "/=") {
		lval /= rval;
	} else if(st.op == "^=") {
		lval = pow(lval, rval);
	} else return -1;

	lref->SetValueByDouble(lval);
	return 0;	
	/*
	// else {
			{
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
			sprintf(msg, "Introspector::ISCommand:  Misunderstood command:  \"%s\"", cmd.c_str());
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
				lvar->SetValueAsString(okfine);
			} else {
#if defined DEBUGEXTRA
			char msg[128];
			sprintf(msg, "Introspector::ISCommand:  Misunderstood command:  \"%s\"", cmd.c_str());
			Logger(msg);
#endif //DEBUGEXTRA
			}
		}
		return 0;
	}*/
	return -1;//CmdSink::ISCommand(cmd);
}

void Introspector::AddIntRef(const string& name, int* ref) {
	if(GetRef(name)) {
		// already exists!
	} else {
		_refs.insert(refpair(name, new IntReference(ref)));
	}
}

void Introspector::AddDoubleRef(const string& name, double* ref) {
	if(GetRef(name)) {
		// already exists
	} else {
		_refs.insert(refpair(name, new DoubleReference(ref)));
	}
}

void Introspector::SetValueByString(const string& name, const string& val) {
	Reference* ref = GetRef(name);
	if(ref) {
		// found it!
		ref->SetValueByString(val);
	} else {
		// named ref not found
	}
}

void Introspector::SetValueByInt(const string& name, int val) {
	Reference* ref = GetRef(name);
	if(ref) {
		// found it
		ref->SetValueByInt(val);
	}
}

void Introspector::SetValueByDouble(const string& name, double val) {
	Reference* ref = GetRef(name);
	if(ref) {
		// found it
		ref->SetValueByDouble(val);
	}
}

string Introspector::GetValueAsString(const string& name) {
	string retval = "";
	Reference* ref = GetRef(name);
	if(ref) retval = ref->GetValueAsString();
	return retval;
}

int Introspector::GetValueAsInt(const string& name) {
	int retval = 0;
	Reference* ref = GetRef(name);
	if(ref) retval = ref->GetValueAsInt();
	return retval;
}

double Introspector::GetValueAsDouble(const string& name) {
	double retval = 0.0;
	Reference* ref = GetRef(name);
	if(ref) retval = ref->GetValueAsDouble();
	return retval;
}

bool Introspector::Exists(const string& name) {
	Reference* ref = GetRef(name);
	if(ref) return true;
	else return false;
}

void Introspector::Clear() {
	for(refitr i = _refs.begin(); i != _refs.end(); i++) {
		delete i->second;
	}
	_refs.clear();
}

Reference* Introspector::GetRef(const string& name) {
	Reference* retval = NULL;
	refitr i = GetRefItr(name);
	if(i != _refs.end()) retval = i->second;
	return retval;
}

refitr Introspector::GetRefItr(const string& name) {
	return _refs.find(name);
}

