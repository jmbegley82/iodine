/* Variable.Test.cpp
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
	char[64] _data;
	dtype _type;
 */

#if defined DEBUG

#include <cstdio>
#include "Variable.h"
#include "Logger.h"

int Variable::Test() {
	Variable* a = new Variable();
	Variable* b = new Variable();
	Variable* c = new Variable();
	a->SetValueAsString("1");
	b->SetValueAsInt(2);
	c->SetValueAsDouble(3);
	char msg[128];
	sprintf(msg, "Variable::Test:  a->GVAS=%s, b->GVAI=%d, c->GVAD=%f", a->GetValueAsString().c_str(),
			b->GetValueAsInt(), c->GetValueAsDouble());
	Logger(msg);
	delete a;
	delete b;
	delete c;
};

#endif //DEBUG
