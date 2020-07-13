/* CmdSink.cpp
 *
 */

#include <string>
#include "CmdSink.h"

using std::string;

int CmdSink::Command(const string& cmd) {
	if(cmd == "test") return CMD_SUCCESS;
	return CMD_INVALID;
}

string CmdSink::RetvalStr(int val) {
	if(val == CMD_SUCCESS) return "CMD_SUCCESS";
	if(val == CMD_INVALID) return "CMD_INVALID";
	string retval = "(";
	retval += std::to_string(val);
	retval += " out of bounds)";
	return retval;
}

#if defined DEBUG
int CmdSink::Test() {
	return 0;
}
#endif //DEBUG
