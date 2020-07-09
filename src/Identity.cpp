/* Identity.cpp
 *
 */

#include <string>
#include "Identity.h"
#include "Timing.h"

using std::string;

Identity::Identity() {
	string identity = "id";
	identity += std::to_string((unsigned int)GetTimeInUsec());
	SetIdentity(identity);
}

Identity::Identity(string identity) {
	SetIdentity(identity);
}

string Identity::GetIdentity() {
	return _identity;
}

void Identity::SetIdentity(string identity) {
	_identity = identity;
}

#if defined DEBUG
int Identity::Test() {
	return 0;
}
#endif //DEBUG
