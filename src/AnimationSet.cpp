/* AnimationSet.cpp
 *
 */

#include <string>
#include "AnimationSet.h"

AnimationSet::AnimationSet() {
}

AnimationSet::~AnimationSet() {
	// TODO: free the texture
	for(asetItr i=_anims.begin(); i!=_anims.end(); i++) {
		delete i->second;
	}
	_anims.clear();
}

void AnimationSet::AddAnimation(const string& name, Animation* anim) {
	if(!GetAnimation(name)) {
		_anims[name] = anim;
	}
}

/*
Animation* AnimationSet::CreateAnimation(const string& name) {
	// like GetAnimation except one is created if it isn't found
	Animation* retval = GetAnimation(name);
	if(!name) {
		retval = new Animation();
		_anims[name] = retval;
	}
	return retval;
}
*/

Animation* AnimationSet::GetAnimation(const string& name) {
	Animation* retval = NULL;
	asetItr i = _anims.find(name);
	//if(i != _anims.end()) retval = i->second;
	if(i == _anims.end()) {
		// not found -- make one, add it to _anims, give it to retval
		retval = new Animation();
		_anims[name] = retval;
	} else {
		// found it
		retval = i->second;
	}
	return retval;
}
