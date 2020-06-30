/* Atom.cpp
 *
 */

#include <string>
#include "Atom.h"

using std::string;

/*
class Atom {
public:
	Atom();			//!< Create a new Atom with a randomized identity.
	Atom(string identity);	//!< Create a new Atom and specify its identity.
	~Atom();		//!< Destruct the Atom.
	string GetIdentity();	//!< Returns the identity of the Atom.
protected:
	string _identity;	//!< The Atom's identity.
};
*/

Atom::Atom() {
	_identity = "totallyrandomnamelol";
}

Atom::Atom(string identity) {
	_identity = identity;
}

Atom::~Atom() {
}

string Atom::GetIdentity() {
	return _identity;
}
