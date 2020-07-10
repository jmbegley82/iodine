/* Atom.Test.cpp
 *
 */

#if defined DEBUG

#include <string>
#include "Atom.h"
#include "Logger.h"

int Atom::Test() {
	Logger("Atom::Test:  a = new Atom() -- create a regular, self-naming Atom.");
	Atom* a = new Atom();
	string id = a->GetIdentity();
	string msg = "Atom::Test:  a->GetIdentity() returned: \"" + id + "\".";
	Logger(msg.c_str());
	Logger("Atom::Test:  deleting a...");
	delete a;
	Logger("Atom::Test:  b = new Atom(\"fancyname\") -- create an Atom with the identity \"fancyname\"");
	Atom* b = new Atom("fancyname");
	id = b->GetIdentity();
	msg = "Atom::Test:  b->GetIdentity() returned: \"" + id + "\".";
	Logger(msg.c_str());

	int rv = b->Command("gibberish");
	msg = "Atom::Test:  b->Command was fed gibberish and emitted the following: " + Atom::RetvalStr(rv);
	Logger(msg.c_str());
	Logger("Atom::Test:  CMD_ERROR was the expected response.");

	rv = b->Command("test-bypass");
	msg = "Atom::Test:  b->Command was fed test-bypass and emitted the following: " + Atom::RetvalStr(rv);
	Logger(msg.c_str());
	Logger("Atom::Test:  CMD_INVALID was the expected response.");

	rv = b->Command("test");
	msg = "Atom::Test:  b->Command was fed test and emitted the following: " + Atom::RetvalStr(rv);
	Logger(msg.c_str());
	Logger("Atom::Test:  CMD_SUCCESS was the expected response.");

	Logger("Atom::Test:  Let's go ahead and manually flush _logbuffer while we're here");
	Logger_process();

	Logger("Atom::Test:  deleting b...");
	delete b;
	return 0;
}
#endif //DEBUG
