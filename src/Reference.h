/* Reference.h
 *
 */

#if !defined REFERENCE_H
#define REFERENCE_H

#include <string>

using std::string;

class Reference {
public:
	Reference();						//!< This ctor does nothing
	~Reference();						//!< This dtor does nothing
	virtual void SetValueByString(const string& val);	//!< Virtual, does nothing
	virtual void SetValueByInt(int val);			//!< Virtual, does nothing
	virtual void SetValueByDouble(double val);		//!< Virtual, does nothing
	virtual string GetValueAsString();			//!< Virtual, returns ""
	virtual int GetValueAsInt();				//!< Virtual, returns 0
	virtual double GetValueAsDouble();			//!< Virtual, returns 0
};

#endif //REFERENCE_H
