/* Atom.cpp
 *
 */

#include <string>
#include "Atom.h"
#include "CmdSink.h"

using std::string;

Atom::Atom() {
	string identity = GetIdentity();
	identity = identity.substr(2);  // remove the 'id' from the beginning...
	identity = "Atom" + identity;   // and replace it with 'Atom'.
	SetIdentity(identity);
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

#if defined DEBUG
int Atom::Test() {
	return 0;
}
#endif //DEBUG
