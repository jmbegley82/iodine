/* VariableSet.h
 *
 */

#if !defined VARIABLESET_H
#define VARIABLESET_H

#include <string>
#include <map>
#include "Variable.h"

using std::string;
using std::map;

class VariableSet {
public:
	VariableSet();
private:
	map<string,Variable> _vars;
};

#endif //VARIABLESET_H
