/* Atom.cpp
 *
 */

#include <string>
#include "Atom.h"
#include "CmdSink.h"

using std::string;

Atom::Atom() {
	SetArbitraryIdentity();
}

Atom::Atom(string identity) {
	SetIdentity(identity);
}

Atom::~Atom() {
}

void Atom::SetArbitraryIdentity() {
	Identity::SetArbitraryIdentity();
	string identity = GetIdentity();
	identity = identity.substr(2);  // remove the 'id' from the beginning...
	identity = "Atom" + identity;   // and replace it with 'Atom'.
	SetIdentity(identity);
}

int Atom::Command(const string cmd) {
	if(cmd == "gibberish") return CMD_ERROR;
	return CmdSink::Command(cmd);
}

string Atom::RetvalStr(int val) {
	if(val == CMD_ERROR) return "CMD_ERROR";
	if(val == CMD_NOPE) return "CMD_NOPE";
	return CmdSink::RetvalStr(val);
}
