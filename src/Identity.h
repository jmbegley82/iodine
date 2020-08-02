/* Identity.h
 *
 */

#if !defined IDENTITY_H
#define IDENTITY_H

#include <string>
using std::string;

//! Anything that needs a string-based identity should inherit this.
class Identity {
public:
	Identity();					//!< Initialize with an arbitrarily-generated identity.
	explicit Identity(const string& identity);	//!< Initialize with a specified identity.
	string GetIdentity();				//!< Return the object's identity.
	void SetIdentity(const string& identity);	//!< @brief Set the object's identity.
							//!< @details Name collision checking not planned at this level.
	virtual void SetArbitraryIdentity();		//!< @brief Rolls a randomized identity
#if defined DEBUG
	static int Test();				//!< Run internal tests
#endif //DEBUG
private:
	string _identity;				//!< The object's identity.
};

#endif //IDENTITY_H
