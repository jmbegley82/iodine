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
	bool _hasBeenAllocated;
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
	sprintf(msg, "Variable::Test:  a->GVAS=%s, a->GVAI=%d, a->GVAD=%f", a->GetValueAsString().c_str(),
			a->GetValueAsInt(), a->GetValueAsDouble());
	Logger(msg);
	sprintf(msg, "Variable::Test:  b->GVAS=%s, b->GVAI=%d, b->GVAD=%f", b->GetValueAsString().c_str(),
			b->GetValueAsInt(), b->GetValueAsDouble());
	Logger(msg);
	sprintf(msg, "Variable::Test:  c->GVAS=%s, c->GVAI=%d, c->GVAD=%f", c->GetValueAsString().c_str(),
			c->GetValueAsInt(), c->GetValueAsDouble());
	Logger(msg);
	delete a;
	delete b;
	delete c;
	return 0;
};

#endif //DEBUG
