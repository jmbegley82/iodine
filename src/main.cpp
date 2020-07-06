/* main.cpp
 * Iodine tests
 *
 */

#include <string>
#include "Logger.h"
#include "Atom.h"

using std::string;

int main(int argc, char** argv) {
	Logger_init();
	Logger("main entered.");

	// start
	Logger("a = new Atom() -- create a regular, self-naming Atom.");
	Atom* a = new Atom();
	string id = a->GetIdentity();
	string msg = "a->GetIdentity() returned: \"" + id + "\".";
	Logger(msg.c_str());
	Logger("deleting a...");
	delete a;
	Logger("b = new Atom(\"fancyname\") -- create an Atom with the identity \"fancyname\"");
	Atom* b = new Atom("fancyname");
	id = b->GetIdentity();
	msg = "b->GetIdentity() returned: \"" + id + "\".";
	Logger(msg.c_str());

	int rv = b->Command("gibberish");
	msg = "b->Command was fed gibberish and emitted the following: " + Atom::RetvalStr(rv);
	Logger(msg.c_str());
	Logger("CMD_ERROR was the expected response.");

	rv = b->Command("test-bypass");
	msg = "b->Command was fed test-bypass and emitted the following: " + Atom::RetvalStr(rv);
	Logger(msg.c_str());
	Logger("CMD_INVALID was the expected response.");

	Logger("Let's go ahead and manually flush _logbuffer while we're here");
	Logger_process();

	Logger("deleting b...");
	delete b;

/*
	// spam the log buffer to make sure it flushes correctly
	for(int i=0; i<1000; i++) {
		Logger("testing the log buffer...");
	}
*/
	// end

	Logger("that's about enough for today.");
	Logger_finish();
	return 0;
}
