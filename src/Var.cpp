/* Var.cpp
 *
 */

#include <string>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "Var.h"
#include "StringManip.h"

using std::string;

Var::Var() {
	Clear();
}

Var::~Var() {
	Clear();
}

int Var::Command(const string& cmd) {
	return CmdSink::Command(cmd);
}

void Var::SetValueAsString(const string& val) {
	Clear();
	//_type = STRING;
	_dataStr = val;
	if(ContainsNumericData(val)) {
		_containsNumericData = true;
		_dataInt = std::stoi(val);
		_dataDbl = std::stod(val);
	} else {
		_containsNumericData = false;
		_dataInt = 0;
		_dataDbl = 0.0;
	}
}

void Var::SetValueAsInt(int val) {
	Clear();
	//_type = INTEGER;
	_containsNumericData = true;
	_dataStr = std::to_string(val);
	_dataInt = val;
	_dataDbl = static_cast<double>(val);
}

void Var::SetValueAsDouble(double val) {
	Clear();
	//_type = DOUBLE;
	_containsNumericData = true;
	_dataStr = std::to_string(val);
	_dataInt = static_cast<int>(round(val));
	_dataDbl = val;
}

void Var::CopyValue(Var* var) {
	//_type = var->_type;
	_containsNumericData = var->_containsNumericData;
	_dataStr = var->_dataStr;
	_dataInt = var->_dataInt;
	_dataDbl = var->_dataDbl;
}

string Var::GetValueAsString() {
	string retval;
	//switch(_type) {
	//case STRING:
	//case INTEGER:
	//case DOUBLE:
		retval = _dataStr;
	//	break;
	//case NONE:
	//default:
	//	retval = "(none)";
	//}
	return retval;
}

int Var::GetValueAsInt() {
	int retval = 0;
	//switch(_type) {
	//case STRING:
	//case INTEGER:
	//case DOUBLE:
		if(_containsNumericData)
			retval = _dataInt;
	//	break;
	//case NONE:
	//default:
	//	break;
	//}
	return retval;
}

double Var::GetValueAsDouble() {
	double retval = 0.0;
	//switch(_type) {
	//case STRING:
	//case INTEGER:
	//case DOUBLE:
		if(_containsNumericData)
			retval = _dataDbl;
	//	break;
	//case NONE:
	//default:
	//	break;
	//}
	return retval;
}

bool Var::IsValidNumericData() {
	return _containsNumericData;
}
/*
bool Var::IsValidNumericData(const string& val) {
	if(val == "") return false;  // no, patrick, nothing is not a number.
	bool retval = false;
	bool keepgoing = true;
	const char* str = val.c_str();
	for(int i=0; i<strlen(str) && keepgoing; i++) {
		if(str[i] != '-' && str[i] != '+' && str[i] != '.' && !isdigit(str[i])) {
			keepgoing = false;
		}
	}
	if(keepgoing) retval = true;
	return retval;
}
*/
void Var::Clear() {
	_dataStr = "";
	_dataInt = 0;
	_dataDbl = 0.0;
	_containsNumericData = false;
	//_type = NONE;
}
