/* DoubleReference.cpp
 *
 */

#include <cmath>
#include "DoubleReference.h"

DoubleReference::DoubleReference(double* ref) {
	SetReference(ref);
}

void DoubleReference::SetReference(double* ref) {
	_ref = ref;
}

void DoubleReference::SetValueByString(const string& val) {
	if(_ref) *_ref = std::stod(val);
}

void DoubleReference::SetValueByInt(int val) {
	if(_ref) *_ref = static_cast<double>(val);
}

void DoubleReference::SetValueByDouble(double val) {
	if(_ref) *_ref = val;
}

string DoubleReference::GetValueAsString() {
	string retval = "";
	if(_ref) {
		retval = std::to_string(*_ref);
	}
	return retval;
}

int DoubleReference::GetValueAsInt() {
	int retval = 0;
	if(_ref) {
		retval = static_cast<int>(round(*_ref));
	}
	return retval;
}

double DoubleReference::GetValueAsDouble() {
	double retval = 0.0;
	if(_ref) {
		retval = *_ref;
	}
	return retval;
}
