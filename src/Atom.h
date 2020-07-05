/* Atom.h
 *
 */

#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "Identity.h"
#include "CmdSink.h"

using std::string;

//! A generic every-object.
class Atom : public Identity, public CmdSink {
public:
	Atom();			//!< Create a new Atom with a randomized identity.
	Atom(string identity);	//!< Create a new Atom and specify its identity.
	~Atom();		//!< Destruct the Atom.
};

#endif //ATOM_H
