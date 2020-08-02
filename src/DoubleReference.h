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
	explicit DoubleReference(double* ref);			//!< Create Reference using given double's address
	~DoubleReference();					//!< It's a dtor
	void SetReference(double* ref);				//!< Set _ref to ref's address
	void SetValueByString(const string& val) override;	//!< Attempt to set _ref's value using a string
	void SetValueByInt(int val) override;			//!< Set _ref's value using an integer
	void SetValueByDouble(double val) override;		//!< Set _ref's value using a double
	string GetValueAsString() override;			//!< Get _ref's current value as a string
	int GetValueAsInt() override;				//!< Get _ref's current value as an integer
	double GetValueAsDouble() override;			//!< Get _ref's current value as a double
private:
	double* _ref;
};

#endif //DOUBLEINTREFERENCE_H
