/* CelString.h
 *
 */

#if !defined CELSTRING_H
#define CELSTRING_H

#include <string>

using std::string;

class CelString {
public:
	CelString(const string& cmd);
	static bool IsValidCelString(const string& cmd);
	bool isValid;
	unsigned int x, y, w, h;
#if defined DEBUG
	static int Test();
#endif //DEBUG
};

#endif //CELSTRING_H
