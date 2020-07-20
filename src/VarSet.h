/* VarSet.h
 *
 */

#if !defined VARSET_H
#define VARSET_H

#include <string>
#include <map>
#include "Var.h"

using std::string;
using std::pair;
using std::map;

typedef map<string,Var*> varmap;
typedef varmap::iterator varitr;
typedef pair<string,Var*> varpair;

class VarSet {
public:
	VarSet();
	~VarSet();
	int VSCommand(const string& cmd);
	//bool AddVar(const string& name, Var* var);
	//void AddVar_forced(const string& name, Var* var);
	//bool CreateVar(const string& name, const string& val);
	void SetVarAsString(const string& name, const string& val);
	void SetVarAsInt(const string& name, int val);
	void SetVarAsDouble(const string& name, double val);
	bool DelVar(const string& name);
	Var* GetVar(const string& name);
	string GetVarAsString(const string& name);
	int GetVarAsInt(const string& name);
	double GetVarAsDouble(const string& name);
	Var Evaluate(const string& cmd);
	void Clear();
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	varmap _vars;
	varitr GetVarItr(const string& name);
};

#endif //VARSET_H
