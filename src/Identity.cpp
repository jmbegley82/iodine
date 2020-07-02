/* Identity.cpp
 *
 */

#include <string>
#include "Identity.h"

using std::string;

string Identity::GetIdentity() {
	return _identity;
}

void Identity::SetIdentity(string identity) {
	_identity = identity;
}
