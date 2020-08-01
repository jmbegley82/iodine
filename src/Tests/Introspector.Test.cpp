/* Introspector.Test.cpp
 *
 */

#if defined DEBUG

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
	is->SetValueByString("testDub", "1.23456");
	isdetail(is, "testDub");
	is->SetValueByString("testInt", "7.89101");
	isdetail(is, "testInt");
	is->ISCommand("testDub = 6.9420");
	isdetail(is, "testDub");
	is->ISCommand("testDub = here have some nonsense");
	is->ISCommand("here's some more nonsense");
	is->ISCommand("testDub = #testInt");
	isdetail(is, "testDub");
	is->ISCommand("testDub = #lolno");
	isdetail(is, "testDub");
	delete is;
	return 0;
}

#endif //DEBUG
