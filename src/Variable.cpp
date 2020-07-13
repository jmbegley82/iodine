/* Variable.cpp
 *
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
	void* _data;
	dtype _type;
 */

#include <string>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "Variable.h"

using std::string;

Variable::Variable() {
	_hasBeenAllocated = false;
	Clear();
}

Variable::~Variable() {
	free(_data);
}

int Variable::Command(const string& cmd) {
	return CmdSink::Command(cmd);
}

void Variable::SetValueAsString(const string& val) {
	Clear();
	_type = STRING;
	_data = malloc(val.length() * sizeof(val.c_str()[0]));
	_hasBeenAllocated = true;
	strncpy((char*)_data, val.c_str(), sizeof(val.c_str()[0]));
}

void Variable::SetValueAsInt(int val) {
	Clear();
	_type = INTEGER;
	_data = malloc(sizeof(val));
	_hasBeenAllocated = true;
	_data = (void*)val;  //static_cast<char*>(val);
}

void Variable::SetValueAsDouble(double val) {
	Clear();
	_type = DOUBLE;
	_data = malloc(sizeof(val));
	_hasBeenAllocated = true;
	_data = val;  //static_cast<char*>(val);
}

string Variable::GetValueAsString() {
	string retval;
	switch(_type) {
	case STRING:
		retval = string((char*)_data);
		break;
	case INTEGER:
		retval = std::to_string((int)_data);  //static_cast<int>(val));
		break;
	case DOUBLE:
		retval = std::to_string((double)_data);  //static_cast<double>(val));
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
		retval = atoi((char*)_data);
		break;
	case INTEGER:
		retval = (int)_data;  //static_cast<int>(_data);
		break;
	case DOUBLE:
		retval = round((double)_data);  //static_cast<double>(_data));
		break;
	case NONE:
	default:
	}
	return retval;
}

double Variable::GetValueAsDouble() {
	double retval = 0.0;
	switch(_type) {
	case STRING:
		retval = strtod((char*)_data, NULL);
		break;
	case INTEGER:
		retval = (double)_data;  //static_cast<double>(_data);
		break;
	case DOUBLE:
		retval = (double)_data;  //static_cast<double>(_data);
		break;
	case NONE:
	default:
	}
	return retval;
}

bool Variable::IsValidNumericData() {
	bool retval = false;
	bool keepgoing = true;
	char* as_cstr = (void*)_data;
	switch(_type) {
	case STRING:
		for(int i=0; i<strlen(as_cstr) && keepgoing; i++) {
			if(as_cstr[i] != '-' && as_cstr[i] != '+' && as_cstr[i] != '.'
				&& !isdigit(as_cstr[i]))
				keepgoing = false;
		}
		if(keepgoing) retval = true;
		break;
	case INTEGER:
		retval = true;
		break;
	case DOUBLE:
		retval = true;
		break;
	case NONE:
	default:
	}
	return retval;
}

void Variable::Clear() {
	_type = NONE;
	if(_hasBeenAllocated) {
		free(_data);
		_hasBeenAllocated = false;
	}
}
