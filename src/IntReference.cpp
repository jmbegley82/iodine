/* IntReference.cpp
 *
 */

#include <string>
#include <cmath>
#include "IntReference.h"

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
