/* Introspector.h
 *
 */

#if !defined INTROSPECTOR_H
#define INTROSPECTOR_H

#include <string>
#include <map>
#include "CmdSink.h"

using std::string;
using std::pair;
using std::map;

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
	Reference* GetRef(const string& name);
	refitr GetRefItr(const string& name);
};

#endif //INTROSPECTOR_H
