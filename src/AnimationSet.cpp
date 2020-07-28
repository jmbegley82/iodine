/* AnimationSet.cpp
 *
 */

#include <string>
#include "AnimationSet.h"

AnimationSet::AnimationSet() {
}

AnimationSet::~AnimationSet() {
	for(asetItr i=_anims.begin(); i!=_anims.end(); ++i) {
		delete i->second;
	}
	_anims.clear();
}

Animation* AnimationSet::LoadAnimation(const string& name, const string& path) {
	Animation* retval = NULL;
	if(!FindAnimation(name)) {
		retval = new Animation();
		retval->LoadScript(path);
		_anims[name] = retval;
	}
	return retval;
}

Animation* AnimationSet::FindAnimation(const string& name) {
	Animation* retval = NULL;
	asetItr i = _anims.find(name);
	if(i == _anims.end()) {
		// not found, don't do anything
	} else {
		// found it
		retval = i->second;
	}
	return retval;
}
