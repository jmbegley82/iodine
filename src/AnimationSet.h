/* AnimationSet.h
 *
 */

#if !defined ANIMATIONSET_H
#define ANIMATIONSET_H

#include <string>
#include <map>
#include "Animation.h"

using std::string;

enum AnimType {
	DEFAULT = 0,
	WALK,
	RUN,
	JUMP,
	ATTACK,
	SPEAK,
	TAUNT,
	ANIMTYPE_COUNT
};

//AnimType DecodeAnimType(char c);

class AnimationSet {
public:
	AnimationSet();						//!< AnimationSet ctor
	~AnimationSet();					//!< AnimationSet dtor
	Animation* LoadAnimation(const char* name, const string& path);
	Animation* FindAnimation(const char* name);
#if defined DEBUG
	static int Test();					//!< Run tests
#endif //DEBUG
private:
	Animation* _anims[ANIMTYPE_COUNT][26];
};

#endif //ANIMATIONSET_H
