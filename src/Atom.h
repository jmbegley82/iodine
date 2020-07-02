/* Atom.h
 *
 */

#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "Identity.h"
using std::string;

//! A generic every-object.
class Atom : public Identity {
public:
	Atom();			//!< Create a new Atom with a randomized identity.
	Atom(string identity);	//!< Create a new Atom and specify its identity.
	~Atom();		//!< Destruct the Atom.
protected:
};

#endif //ATOM_H
