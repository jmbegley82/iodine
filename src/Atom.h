/* Atom.h
 *
 */

#if !defined ATOM_H
#define ATOM_H

#include <string>
#include "Identity.h"
#include "CmdSink.h"
#include "Ticker.h"

using std::string;

//! A generic every-object.
class Atom : public Identity, public CmdSink, public Ticker {
public:
	Atom();					//!< Create a new Atom with a randomized identity.
	Atom(string identity);			//!< Create a new Atom and specify its identity.
	~Atom();				//!< Destruct the Atom.
	virtual int Command(const string cmd);	//!< Attempts to consume cmd.  Let's just return CMD_ERROR for now.
	static string RetvalStr(int val);	//!< Converts val into a string representation of the Retval.
#if defined DEBUG
	static int Test();			//!< Run internal tests
#endif //DEBUG
private:
	/**
	 * Some arbitrary extra Retvals
	 */
	enum Retval {
		CMD_ERROR = 0x2000,		//!< The command was syntactically correct but failed anyway
		CMD_NOPE			//!< Some other such nonsense, for testing purposes
	};
};

#endif //ATOM_H
