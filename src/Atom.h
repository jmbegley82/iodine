/* Atom.h
 *
 */

#if !defined ATOM_H
#define ATOM_H

#include <string>
#include "Identity.h"
#include "Ticker.h"
#include "Introspector.h"
#include "Motion.h"

using std::string;

//! A generic every-object.
class Atom : public Identity, public Motion, public Ticker, public Introspector {
public:
	Atom();					//!< Create a new Atom with a randomized identity.
	explicit Atom(const string& identity);	//!< Create a new Atom and specify its identity.
	~Atom();				//!< Destruct the Atom.
	void SetArbitraryIdentity() override;	//!< Override Identity:: so ours starts with 'atom' and not 'id'
	int AtomCommand(const string& cmd);	//!< Attempts to consume cmd.  Let's just return CMD_ERROR for now.
	static string RetvalStr(int val);	//!< Converts val into a string representation of the Retval.
#if defined DEBUG
	static int Test();			//!< Run internal tests
#endif //DEBUG
private:
	/**
	 * Some arbitrary extra Retvals
	 */
	enum AtomCmdRetvals {
		CMD_ERROR = 0x2000,		//!< The command was syntactically correct but failed anyway
		CMD_NOPE,			//!< Some other such nonsense, for testing purposes
		CMD_CONSUMED,			//!< The command string was processed successfully
		CMD_UNCONSUMED			//!< The command string was unconsumed
	};
	void SetRefs();				//!< Sets up Atom-specific Introspector References
};

#endif //ATOM_H
