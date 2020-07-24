/* Introspector.h
 *
 */

#if !defined INTROSPECTOR_H
#define INTROSPECTOR_H

#include <string>
#include <map>
#include "Reference.h"

using std::string;
using std::pair;
using std::map;

typedef map<string,Reference*> refmap;					//!< container type for References
typedef refmap::iterator refitr;					//!< approrpiate iterator for refmap
typedef pair<string,Reference*> refpair;				//!< appropriate std::pair for refmap (is this needed?)

class Introspector {
public:
	Introspector();							//!< It's a ctor
	~Introspector();						//!< It's a dtor, it deletes whatever's in _refs
	int ISCommand(const string& cmd);				//!< Process text commands related to _refs
	void AddIntRef(const string& name, int* ref);			//!< Add a reference to an integer value
	void AddDoubleRef(const string& name, double* ref);		//!< Add a reference to a double value
	void SetValueByString(const string& name, const string& val);	//!< Attempt to set named ref's value using a string
	void SetValueByInt(const string& name, int val);		//!< Set named ref's value using an integer
	void SetValueByDouble(const string& name, double val);		//!< Set named ref's value using a double
	string GetValueAsString(const string& name);			//!< Get named ref's value as a string
	int GetValueAsInt(const string& name);				//!< Get named ref's value as an integer
	double GetValueAsDouble(const string& name);			//!< Get named ref's value as a double
	bool Exists(const string& name);				//!< Return true if named reference exists
	void Clear();							//!< Remove all currently-held references
#if defined DEBUG
	static int Test();						//!< Run tests
#endif //DEBUG
private:
	refmap _refs;
	Reference* GetRef(const string& name);				//!< Get pointer to named reference
	refitr GetRefItr(const string& name);				//!< Get refmap iterator for named reference
};

#endif //INTROSPECTOR_H
