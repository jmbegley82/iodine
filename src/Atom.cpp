/* Atom.cpp
 *
 */

#include <string>
#include "Atom.h"

using std::string;

Atom::Atom() {
	SetIdentity("totallyrandomnamelol");
}

Atom::Atom(string identity) {
	SetIdentity(identity);
}

Atom::~Atom() {
}
