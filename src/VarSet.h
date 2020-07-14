/* VarSet.h
 *
 */

#if !defined VARSET_H
#define VARSET_H

#include <string>
#include <map>
#include "CmdSink.h"
#include "Var.h"

using std::string;
using std::pair;
using std::map;

typedef map<string,Var*> varmap;
typedef varmap::iterator varitr;
typedef pair<string,Var*> varpair;

class VarSet : public CmdSink {
public:
	VarSet();
	~VarSet();
	int Command(const string& cmd);
	bool AddVar(const string& name, Var* var);
	void AddVar_forced(const string& name, Var* var);
	bool DelVar(const string& name);
	Var* GetVar(const string& name);
	string GetVarAsString(const string& name);
	int GetVarAsInt(const string& name);
	double GetVarAsDouble(const string& name);
	void Clear();
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	varmap _vars;
	varitr GetVarItr(const string& name);
};

#endif //VARSET_H
