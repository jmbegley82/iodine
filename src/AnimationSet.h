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
	Animation* LoadAnimation(const string& name, const string& path);
	Animation* FindAnimation(const string& name);
#if defined DEBUG
	static int Test();					//!< Run tests
#endif //DEBUG
private:
	animSet _anims;
};

#endif //ANIMATIONSET_H
