/* Variable.h
 *
 */

#if !defined VARIABLE_H
#define VARIABLE_H

#include <string>
#include "CmdSink.h"

using std::string;

class Variable : public CmdSink {
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
};

#endif //VARIABLE_H
