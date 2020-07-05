/* CmdSink.cpp
 *
 */

#include <string>
#include "CmdSink.h"

using std::string;
using Retval = CmdSink::Retval;

Retval CmdSink::Command(const string cmd) {
	return CMD_INVALID;
}

string CmdSink::RetvalStr(Retval val) {
	string retval = "(out of bounds)";
	if     (val == CMD_SUCCESS) retval = "CMD_SUCCESS";
	else if(val == CMD_INVALID) retval = "CMD_INVALID";
	return retval;
}
