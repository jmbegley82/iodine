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
	DoubleReference();
	DoubleReference(double* ref);
	~DoubleReference();
	void SetReference(double* ref);
	virtual void SetValueByString(const string& val);
	virtual void SetValueByInt(int val);
	virtual void SetValueByDouble(double val);
	virtual string GetValueAsString();
	virtual int GetValueAsInt();
	virtual double GetValueAsDouble();
private:
	double* _ref;
};

#endif //DOUBLEINTREFERENCE_H
