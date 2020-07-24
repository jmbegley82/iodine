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

typedef map<string,Var*> varmap;		//!< map for containing Vars
typedef varmap::iterator varitr;		//!< relevant iterator for varmap
typedef pair<string,Var*> varpair;		//!< relevant std::pair for varmap

class VarSet {
public:
	VarSet();							//!< initialize
	~VarSet();							//!< deinit
	int VSCommand(const string& cmd);				//!< Interpret text command
	//bool AddVar(const string& name, Var* var);
	//void AddVar_forced(const string& name, Var* var);
	//bool CreateVar(const string& name, const string& val);
	void SetVarAsString(const string& name, const string& val);	//!< Set Var value to string
	void SetVarAsInt(const string& name, int val);			//!< Set Var value to integer
	void SetVarAsDouble(const string& name, double val);		//!< Set Var value to double
	bool DelVar(const string& name);				//!< Delete Var
	Var* GetVar(const string& name);				//!< Return ptr to named Var (or NULL if not found)
	string GetVarAsString(const string& name);			//!< Return value as a string
	int GetVarAsInt(const string& name);				//!< Return value as an integer
	double GetVarAsDouble(const string& name);			//!< Return value as a double
	Var Evaluate(const string& cmd);				//!< Interpret value of string cmd
	void Clear();							//!< Delete all Vars
#if defined DEBUG
	static int Test();						//!< Run tests
#endif //DEBUG
private:
	varmap _vars;
	varitr GetVarItr(const string& name);				//!< Return iterator pointing to named Var
};

#endif //VARSET_H
