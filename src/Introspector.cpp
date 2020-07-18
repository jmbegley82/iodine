/* Introspector.cpp
 *
 */

#include <cmath>
#include "Introspector.h"

/*
class Reference {
public:
	Reference();
	~Reference();
	virtual void SetValueByString(const string& val);
	virtual void SetValueByInt(int val);
	virtual void SetValueByDouble(double val);
	virtual string GetValueAsString();
	virtual int GetValueAsInt();
	virtual double GetValueAsDouble();
private:
};
*/

Reference::Reference() {
}

Reference::~Reference() {
}

void Reference::SetValueByString(const string& val) {
}

void Reference::SetValueByInt(int val) {
}

void Reference::SetValueByDouble(double val) {
}

string Reference::GetValueAsString() {
	return "";
}

int Reference::GetValueAsInt() {
	return 0;
}

double Reference::GetValueAsDouble() {
	return 0.0;
}

/*
class IntReference : public Reference {
public:
	IntReference();
	IntReference(int* ref);
	~IntReference();
	void SetReference(int* ref);
	virtual void SetValueByString(const string& val);
	virtual void SetValueByInt(int val);
	virtual void SetValueByDouble(double val);
	virtual string GetValueAsString();
	virtual int GetValueAsInt();
	virtual double GetValueAsDouble();
private:
	int* _ref;
};
*/

IntReference::IntReference(int* ref) {
	SetReference(ref);
}

void IntReference::SetReference(int* ref) {
	_ref = ref;
}

void IntReference::SetValueByString(const string& val) {
	if(_ref) *_ref = std::stoi(val);  // TODO:  any kind of checking whatsoever
}

void IntReference::SetValueByInt(int val) {
	if(_ref) *_ref = val;
}

void IntReference::SetValueByDouble(double val) {
	if(_ref) *_ref = static_cast<int>(round(val));
}

string IntReference::GetValueAsString() {
	string retval = "";
	if(_ref) {
		retval = std::to_string(*_ref);
	}
	return retval;
}

int IntReference::GetValueAsInt() {
	int retval = 0;
	if(_ref) {
		retval = *_ref;
	}
	return retval;
}

double IntReference::GetValueAsDouble() {
	double retval = 0.0;
	if(_ref) {
		retval = static_cast<double>(*_ref);
	}
	return retval;
}

/*
class DoubleReference : public Reference {
public:
	DoubleReference();
	DoubleReference(double* ref);
	~DoubleReference();
	void SetReference(double* ref);
	virtual void SetValueByString(const string& val);
	virtual void SetValueByInt(int val);
	virtual void SetValueByDouble(double val);
	virtual string GetValueAsString();
	virtual int GetValueAsInt();
	virtual double GetValueAsDouble();
private:
	double* _ref;
};
*/

DoubleReference::DoubleReference(double* ref) {
	SetReference(ref);
}

void DoubleReference::SetReference(double* ref) {
	_ref = ref;
}

void DoubleReference::SetValueByString(const string& val) {
	if(_ref) *_ref = std::stod(val);
}

void DoubleReference::SetValueByInt(int val) {
	if(_ref) *_ref = static_cast<double>(val);
}

void DoubleReference::SetValueByDouble(double val) {
	if(_ref) *_ref = val;
}

string DoubleReference::GetValueAsString() {
	string retval = "";
	if(_ref) {
		retval = std::to_string(*_ref);
	}
	return retval;
}

int DoubleReference::GetValueAsInt() {
	int retval = 0;
	if(_ref) {
		retval = static_cast<int>(round(*_ref));
	}
	return retval;
}

double DoubleReference::GetValueAsDouble() {
	double retval = 0.0;
	if(_ref) {
		retval = *_ref;
	}
	return retval;
}

/*
typedef map<string,Reference*> refmap;
typedef refmap::iterator refitr;
typedef pair<string,Reference*> refpair;

class Introspector : public CmdSink {
public:
	Introspector();
	~Introspector();
	int Command(const string& cmd);
	void AddIntRef(const string& name, int* ref);
	void AddDoubleRef(const string& name, double* ref);
	void SetValueByString(const string& name, const string& val);
	void SetValueByInt(const string& name, int val);
	void SetValueByDouble(const string& name, double val);
	string GetValueAsString(const string& name);
	int GetValueAsInt(const string& name);
	double GetValueAsDouble(const string& name);
	void Clear();
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	refmap _refs;
	refitr GetItr(const string& name);
};
*/

Introspector::Introspector() {
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
