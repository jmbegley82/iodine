/* Iodine tests
 *
 */

#include <string>
#include "Logger.h"
#include "Atom.h"

using std::string;

int main(int argc, char** argv) {
	Logger("main entered.");
	Atom* a = new Atom();
	string id = a->GetIdentity();
	string amsg = "a->GetIdentity() returned: \"" + id + "\".";
	Logger(amsg.c_str());
	Logger("that's about enough for today.");
	return 0;
}
