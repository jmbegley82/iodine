/* Identity.cpp
 *
 */

#include <string>
#include "Identity.h"
#include "Timing.h"

using std::string;

Identity::Identity() {
	this->SetArbitraryIdentity();
}

Identity::Identity(const string& identity) {
	SetIdentity(identity);
}

string Identity::GetIdentity() {
	return _identity;
}

void Identity::SetIdentity(const string& identity) {
	_identity = identity;
}

void Identity::SetArbitraryIdentity() {
	string identity = "id";
	identity += std::to_string((unsigned int)GetTimeInUsec());
	SetIdentity(identity);
}

#if defined DEBUG
int Identity::Test() {
	return 0;
}
#endif //DEBUG
