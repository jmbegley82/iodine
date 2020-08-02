/* CelString.h
 *
 */

#if !defined CELSTRING_H
#define CELSTRING_H

#include <string>

using std::string;

class CelString {
public:
	explicit CelString(const string& cmd);				//!< CelString ctor/main function
	static bool IsValidCelString(const string& cmd);	//!< Checks if given string is valid for use by our ctor
	bool isValid;						//!< True if constructed with a valid string, false otherwise
	unsigned int x;						//!< X position of upper left corner of Cel in spritesheet
	unsigned int y;						//!< Y position of upper left corner of Cel in spritesheet
	unsigned int w;						//!< Width of Cel
	unsigned int h;						//!< Height of Cel
#if defined DEBUG
	static int Test();					//!< Run tests
#endif //DEBUG
};

#endif //CELSTRING_H
