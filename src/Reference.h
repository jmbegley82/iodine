/* Reference.h
 *
 */

#if !defined REFERENCE_H
#define REFERENCE_H

#include <string>

using std::string;

class Reference {
public:
	Reference();
	~Reference();
	virtual void SetValueByString(const string& val);
	virtual void SetValueByInt(int val);
	virtual void SetValueByDouble(double val);
	virtual string GetValueAsString();
	virtual int GetValueAsInt();
	virtual double GetValueAsDouble();
private:
};

#endif //REFERENCE_H
