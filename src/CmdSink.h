/* CmdSink.h
 *
 */

#if !defined CMDSINK_H
#define CMDSINK_H

#include <string>
using std::string;

//! Anything that can execute a Command string should inherit this.
class CmdSink {
public:
	virtual int Command(const string cmd);		//!< Attempts to consume cmd.  This base class just returns CMD_INVALID.
	static string RetvalStr(int val);		//!< Converts val into a string representation of the Retval.
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	/**
	 * Return values for Command
	 * Enum values can be turned to strings using RetvalStr
	 */
	enum Retval {
		CMD_SUCCESS = 0x1000,			//!< CMD_SUCCESS indicates that the string was successfully consumed.
		CMD_INVALID				//!< CMD_INVALID indicates that the string was not successfully consumed.
	};
};

#endif //CMDSINK_H
