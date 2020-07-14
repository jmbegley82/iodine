/* Variable.Test.cpp
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

#if defined DEBUG

#include <cstdio>
#include "Variable.h"
#include "Logger.h"

void vdetail(const char* name, Variable* var) {
	char msg[128];
	sprintf(msg, "Variable::Test:  vdetail:  %s->GVAI=%d, %s->GVAD=%16f, %s->GVAS=%s", name, var->GetValueAsInt(), name,
		var->GetValueAsDouble(), name, var->GetValueAsString().c_str());
	Logger(msg);
}

int Variable::Test() {
	Variable* a = new Variable();
	Variable* b = new Variable();
	Variable* c = new Variable();
	a->SetValueAsString("1");
	b->SetValueAsInt(2);
	c->SetValueAsDouble(3);
	vdetail("a", a);
	vdetail("b", b);
	vdetail("c", c);
	delete a;
	delete b;
	delete c;
	return 0;
}

#endif //DEBUG
