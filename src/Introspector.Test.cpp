/* Introspector.Test.cpp
 *
 */

#include "Introspector.h"
#include "Logger.h"

using std::string;

void isdetail(Introspector* is, string name) {
	char msg[128];
	if(is->Exists(name)) {
		sprintf(msg, "Introspector::Test:  %s: int=%d, double=%f", name.c_str(), is->GetValueAsInt(name),
			is->GetValueAsDouble(name));
	} else {
		sprintf(msg, "Introspector::Test:  %s not found!", name.c_str());
	}
	Logger(msg);
}

int Introspector::Test() {
	int retval = 0;
	int testInt = -65535;
	double testDub = 3.14159;
	Introspector* is = new Introspector();
	is->AddIntRef("testInt", &testInt);
	is->AddDoubleRef("testDub", &testDub);
	isdetail(is, "testInt");
	isdetail(is, "testDub");
	isdetail(is, "doesntexist");
	delete is;
	return 0;
}
