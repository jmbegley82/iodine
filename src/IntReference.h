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
	explicit IntReference(int* ref);			//!< Create Reference using address of ref
	~IntReference();					//!< It's a dtor
	void SetReference(int* ref);				//!< Set _ref to address of int ref
	void SetValueByString(const string& val) override;	//!< Attempt to set value using a string
	void SetValueByInt(int val) override;			//!< Set value using an integer
	void SetValueByDouble(double val) override;		//!< Set value using a (rounded) double
	string GetValueAsString() override;			//!< Get value as a string
	int GetValueAsInt() override;				//!< Get value as an integer
	double GetValueAsDouble() override;			//!< Get value as a double
private:
	int* _ref;
};

#endif //INTREFERENCE_H
