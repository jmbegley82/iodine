/* CmdSink.h
 *
 */

#ifndef CMDSINK_H
#define CMDSINK_H

#include <string>
using std::string;

//! Anything that can execute a Command string should inherit this.
class CmdSink {
public:
	/**
	 * Return values for Command
	 * Enum values can be turned to strings using RetvalStr
	 */
	enum Retval {
		CMD_SUCCESS,			//!< CMD_SUCCESS indicates that the string was successfully consumed.
		CMD_INVALID			//!< CMD_INVALID indicates that the string was not successfully consumed.
	};
	Retval Command(const string cmd);	//!< Attempts to consume cmd.  This base class just returns CMD_INVALID.
	static string RetvalStr(Retval val);	//!< Converts val into a string representation of the Retval.
};

#endif //CMDSINK_H
