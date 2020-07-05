/* Identity.h
 *
 */

#ifndef IDENTITY_H
#define IDENTITY_H

#include <string>
using std::string;

//! Anything that needs a string-based identity should inherit this.
class Identity {
public:
	string GetIdentity();			//!< Return the object's identity
	void SetIdentity(string identity);	//!< Set the object's identity
private:
	string _identity;			//!< The object's identity.
};

#endif //IDENTITY_H
