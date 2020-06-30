/* Atom.h
 *
 */

#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;

//! A generic every-object.
class Atom {
public:
	Atom();			//!< Create a new Atom with a randomized identity.
	Atom(string identity);	//!< Create a new Atom and specify its identity.
	~Atom();		//!< Destruct the Atom.
	string GetIdentity();	//!< Returns the identity of the Atom.
protected:
	string _identity;	//!< The Atom's identity.
};

#endif //ATOM_H
