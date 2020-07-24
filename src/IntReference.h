/* IntReference.h
 *
 */

#if !defined INTREFERENCE_H
#define INTREFERENCE_H

#include <string>
#include "Reference.h"

using std::string;

class IntReference : public Reference {
public:
	IntReference();						//!< It's a ctor
	IntReference(int* ref);					//!< Create Reference using address of ref
	~IntReference();					//!< It's a dtor
	void SetReference(int* ref);				//!< Set _ref to address of int ref
	virtual void SetValueByString(const string& val);	//!< Attempt to set value using a string
	virtual void SetValueByInt(int val);			//!< Set value using an integer
	virtual void SetValueByDouble(double val);		//!< Set value using a (rounded) double
	virtual string GetValueAsString();			//!< Get value as a string
	virtual int GetValueAsInt();				//!< Get value as an integer
	virtual double GetValueAsDouble();			//!< Get value as a double
private:
	int* _ref;
};

#endif //INTREFERENCE_H
