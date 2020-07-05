/* main.cpp
 * Iodine tests
 *
 */

#include <string>
#include "Logger.h"
#include "Atom.h"

using std::string;

int main(int argc, char** argv) {
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

	CmdSink::Retval rv = b->Command("nonsense command that will be rejected anyway");
	msg = "b->Command was fed gibberish and emitted the following: " + CmdSink::RetvalStr(rv);
	Logger(msg.c_str());
	Logger("CMD_INVALID was the expected response.");

	Logger("deleting b...");
	delete b;
	// end

	Logger("that's about enough for today.");
	return 0;
}
