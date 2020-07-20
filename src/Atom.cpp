/* Atom.cpp
 *
 */

#include <string>
#include "Atom.h"
#include "Motion.h"
#include "Geometry.h"

using std::string;

Atom::Atom() {
	SetArbitraryIdentity();
	SetRefs();
}

Atom::Atom(const string& identity) {
	SetIdentity(identity);
	SetRefs();
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

int Atom::AtomCommand(const string& cmd) {
	if(cmd == "gibberish") return CMD_ERROR;
	int retval = ISCommand(cmd);
	if(retval >= 0) return CMD_CONSUMED;
	return CMD_UNCONSUMED;
}

string Atom::RetvalStr(int val) {
	if(val == CMD_ERROR) return "CMD_ERROR";
	if(val == CMD_NOPE) return "CMD_NOPE";
	if(val == CMD_CONSUMED) return "CMD_CONSUMED";
	if(val == CMD_UNCONSUMED) return "CMD_UNCONSUMED";
	return "(invalid)";
}

void Atom::SetRefs() {
	AddDoubleRef("pos.x", GetPosXPtr());
	AddDoubleRef("pos.y", GetPosYPtr());
	AddDoubleRef("size.w", GetSizeWPtr());
	AddDoubleRef("size.h", GetSizeHPtr());
	AddDoubleRef("offset.x", GetCenterXPtr());
	AddDoubleRef("offset.y", GetCenterYPtr());
	AddDoubleRef("vel.x", GetVelocityXPtr());
	AddDoubleRef("vel.y", GetVelocityYPtr());
}
