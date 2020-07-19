/* Var.h
 *
 */

#if !defined VAR_H
#define VAR_H

#include <string>
#include "CmdSink.h"

using std::string;

class Var : public CmdSink {
public:
	Var();							//!< Construct the Var
	~Var();							//!< Destruct the Var
	int Command(const string& cmd);				//!< Pass a command string to the Var (NI)
	void SetValueAsString(const string& val);		//!< Set the Var's value to val
	void SetValueAsInt(int val);				//!< Set the Var's value to val
	void SetValueAsDouble(double val);			//!< Set the Var's value to val
	void CopyValue(Var* var);
	string GetValueAsString();				//!< Get a string representing the Var
	int GetValueAsInt();					//!< Get an int representing the Var
	double GetValueAsDouble();				//!< Get a double representing the Var
	bool IsValidNumericData();				//!< Returns _containsNumericData
	//static bool IsValidNumericData(const string& val);	//!< Static function to determine validity of numeric data
								//!<   in a string
	void Clear();						//!< Empty the Var and set type to NONE
#if defined DEBUG
	static int Test();					//!< Run tests in Var.Test.cpp
#endif //DEBUG
private:
	string _dataStr;					//!< Our data represented by a string
	int _dataInt;						//!< Our data represented by an int when possible
	double _dataDbl;					//!< Our data represented by a double when possible
	bool _containsNumericData;				//!< The Var contains meaningful numeric data
};

#endif //VAR_H
