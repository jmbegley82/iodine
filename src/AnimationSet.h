/* AnimationSet.h
 *
 */

#if !defined ANIMATIONSET_H
#define ANIMATIONSET_H

#include <string>
#include <map>
#include "Animation.h"

using std::string;
using std::map;

typedef map<string,Animation*> animSet;		//!< container for Animations
typedef animSet::iterator asetItr;		//!< relevant iterator for animSet

class AnimationSet {
public:
	AnimationSet();						//!< AnimationSet ctor
	~AnimationSet();					//!< AnimationSet dtor
	void AddAnimation(const string& name, Animation* anim);	//!< Add new Animation with the given name
	//Animation* CreateAnimation(const string& name);	//!< Deprecated
	Animation* GetAnimation(const string& name);		//!< Get Animation by name (or NULL if not found)
#if defined DEBUG
	static int Test();					//!< Run tests
#endif //DEBUG
private:
	animSet _anims;
};

#endif //ANIMATIONSET_H
