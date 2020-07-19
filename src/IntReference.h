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
	IntReference();
	IntReference(int* ref);
	~IntReference();
	void SetReference(int* ref);
	virtual void SetValueByString(const string& val);
	virtual void SetValueByInt(int val);
	virtual void SetValueByDouble(double val);
	virtual string GetValueAsString();
	virtual int GetValueAsInt();
	virtual double GetValueAsDouble();
private:
	int* _ref;
};

#endif //INTREFERENCE_H
