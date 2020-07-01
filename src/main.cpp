/* Iodine tests
 *
 */

#include <string>
#include "Logger.h"
#include "Atom.h"

using std::string;

int main(int argc, char** argv) {
	Logger("main entered.");
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
	Logger("deleting b...");
	delete b;
	Logger("that's about enough for today.");
	return 0;
}
