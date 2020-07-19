/* Introspector.cpp
 *
 */

#include <cmath>
#include "Introspector.h"
#include "IntReference.h"
#include "DoubleReference.h"

Introspector::Introspector() {
}

Introspector::~Introspector() {
	Clear();
}

int Introspector::Command(const string& cmd) {
	return CmdSink::Command(cmd);
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

