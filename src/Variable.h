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
	Variable();						//!< Construct the variable
	~Variable();						//!< Destruct the variable
	int Command(const string& cmd);				//!< Pass a command string to the variable (NI)
	void SetValueAsString(const string& val);		//!< Set the variable's value to val
	void SetValueAsInt(int val);				//!< Set the variable's value to val
	void SetValueAsDouble(double val);			//!< Set the variable's value to val
	string GetValueAsString();				//!< Get a string representing the variable
	int GetValueAsInt();					//!< Get an int representing the variable
	double GetValueAsDouble();				//!< Get a double representing the variable
	bool IsValidNumericData();				//!< Returns _containsNumericData
	static bool IsValidNumericData(const string& val);	//!< Static function to determine validity of numeric data
								//!<   in a string
	void Clear();						//!< Make the variable as empty as possible and set type to NONE
#if defined DEBUG
	static int Test();					//!< Run tests in Variable.Test.cpp
#endif //DEBUG
private:
	enum dtype {
		NONE,						//!< The variable is not initialized
		STRING,						//!< The variable was initialized with a string
		DOUBLE,						//!< The variable was initialized with a double
		INTEGER						//!< The variable was initialized with an integer
	};
	//void* _data;
	string _dataStr;					//!< Our data represented by a string
	int _dataInt;						//!< Our data represented by an int when possible
	double _dataDbl;					//!< Our data represented by a double when possible
	dtype _type;						//!< The dtype with which we were initialized
	bool _containsNumericData;				//!< The variable contains meaningful numeric data
//	bool _hasBeenAllocated;					//!< (Deprecated)
};

#endif //VARIABLE_H
