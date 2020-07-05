/* CmdSink.cpp
 *
 */

#include <string>
#include "CmdSink.h"

using std::string;

int CmdSink::Command(const string cmd) {
	return CMD_INVALID;
}

string CmdSink::RetvalStr(int val) {
	if(val == CmdSink::Retval::CMD_SUCCESS) return "CMD_SUCCESS";
	if(val == CmdSink::Retval::CMD_INVALID) return "CMD_INVALID";
	string retval = "(";
	retval += std::to_string(val);
	retval += " out of bounds)";
	return retval;
}
