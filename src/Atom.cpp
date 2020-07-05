/* Atom.cpp
 *
 */

#include <string>
#include "Atom.h"
#include "CmdSink.h"

using std::string;

Atom::Atom() {
	SetIdentity("totallyrandomnamelol");
}

Atom::Atom(string identity) {
	SetIdentity(identity);
}

Atom::~Atom() {
}

int Atom::Command(const string cmd) {
	if(cmd == "gibberish") return Atom::Retval::CMD_ERROR;
	return CmdSink::Command(cmd);
}

string Atom::RetvalStr(int val) {
	if(val == Atom::Retval::CMD_ERROR) return "CMD_ERROR";
	if(val == Atom::Retval::CMD_NOPE) return "CMD_NOPE";
	return CmdSink::RetvalStr(val);
}
