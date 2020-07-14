/* Variable.cpp
 *
public:
	Variable();
	~Variable();
	int Command(const string& cmd);
	void SetValueAsString(const string& val);
	void SetValueAsInt(int val);
	void SetValueAsDouble(double val);
	string GetValueAsString();
	int GetValueAsInt();
	double GetValueAsDouble();
	bool IsValidNumericData();
	static bool IsValidNumericData(const string& val);
	void Clear();
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	enum dtype {
		NONE,
		STRING,
		DOUBLE,
		INTEGER
	};
	//void* _data;
	string _dataStr;
	int _dataInt;
	double _dataDbl;
	dtype _type;
	bool _containsNumericData;
//	bool _hasBeenAllocated;
 */

#include <string>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "Variable.h"

using std::string;

Variable::Variable() {
	Clear();
}

Variable::~Variable() {
	Clear();
}

int Variable::Command(const string& cmd) {
	return CmdSink::Command(cmd);
}

void Variable::SetValueAsString(const string& val) {
	Clear();
	_type = STRING;
	_dataStr = val;
	if(IsValidNumericData(val)) {
		_containsNumericData = true;
		_dataInt = std::stoi(val);
		_dataDbl = std::stod(val);
	} else {
		_containsNumericData = false;
		_dataInt = 0;
		_dataDbl = 0.0;
	}
}

void Variable::SetValueAsInt(int val) {
	Clear();
	_type = INTEGER;
	_containsNumericData = true;
	_dataStr = std::to_string(val);
	_dataInt = val;
	_dataDbl = static_cast<double>(val);
}

void Variable::SetValueAsDouble(double val) {
	Clear();
	_type = DOUBLE;
	_containsNumericData = true;
	_dataStr = std::to_string(val);
	_dataInt = static_cast<int>(round(val));
	_dataDbl = val;
}

string Variable::GetValueAsString() {
	string retval;
	switch(_type) {
	case STRING:
	case INTEGER:
	case DOUBLE:
		retval = _dataStr;
		break;
	case NONE:
	default:
		retval = "(invalid)";
	}
	return retval;
}

int Variable::GetValueAsInt() {
	int retval = 0;
	switch(_type) {
	case STRING:
	case INTEGER:
	case DOUBLE:
		if(_containsNumericData)
			retval = _dataInt;
		break;
	case NONE:
	default:
		break;
	}
	return retval;
}

double Variable::GetValueAsDouble() {
	double retval = 0.0;
	switch(_type) {
	case STRING:
	case INTEGER:
	case DOUBLE:
		if(_containsNumericData)
			retval = _dataDbl;
		break;
	case NONE:
	default:
		break;
	}
	return retval;
}

bool Variable::IsValidNumericData() {
	return _containsNumericData;
}

bool Variable::IsValidNumericData(const string& val) {
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

void Variable::Clear() {
	_dataStr = "";
	_dataInt = 0;
	_dataDbl = 0.0;
//	_hasBeenAllocated = false;
	_containsNumericData = false;
	_type = NONE;
}
