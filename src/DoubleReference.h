/* DoubleReference.h
 *
 */

#if !defined DOUBLEINTREFERENCE_H
#define DOUBLEINTREFERENCE_H

#include <string>
#include "Reference.h"

using std::string;

class DoubleReference : public Reference {
public:
	DoubleReference();					//!< It's a ctor
	DoubleReference(double* ref);				//!< Create Reference using given double's address
	~DoubleReference();					//!< It's a dtor
	void SetReference(double* ref);				//!< Set _ref to ref's address
	virtual void SetValueByString(const string& val);	//!< Attempt to set _ref's value using a string
	virtual void SetValueByInt(int val);			//!< Set _ref's value using an integer
	virtual void SetValueByDouble(double val);		//!< Set _ref's value using a double
	virtual string GetValueAsString();			//!< Get _ref's current value as a string
	virtual int GetValueAsInt();				//!< Get _ref's current value as an integer
	virtual double GetValueAsDouble();			//!< Get _ref's current value as a double
private:
	double* _ref;
};

#endif //DOUBLEINTREFERENCE_H
