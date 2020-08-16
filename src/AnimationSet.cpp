/* AnimationSet.cpp
 *
 */

#include <string>
#include "AnimationSet.h"

AnimationSet::AnimationSet() {
	for(int i=0; i<256; ++i) {
		for(int j=0; j<256; ++j) {
			_anims[i][j] = NULL;
		}
	}
}

AnimationSet::~AnimationSet() {
	/*
	for(asetItr i=_anims.begin(); i!=_anims.end(); ++i) {
		delete i->second;
	}
	_anims.clear();
	*/
	for(int i=0; i<256; ++i) {
		for(int j=0; j<256; ++j) {
			if(_anims[i][j]) delete _anims[i][j];
		}
	}
}

Animation* AnimationSet::LoadAnimation(const char* name, const string& path) {
	Animation* retval = NULL;
	/*
	if(!FindAnimation(name)) {
		retval = new Animation();
		retval->LoadScript(path);
		_anims[name] = retval;
	}
	*/
	char x = name[0];
	char y = name[1];
	if(_anims[x][y]) {
		retval = _anims[x][y];
	} else {
		retval = new Animation();
		retval->LoadScript(path);
		_anims[x][y] = retval;
	}
	return retval;
}

Animation* AnimationSet::FindAnimation(const char* name) {
	Animation* retval = NULL;
	/*
	asetItr i = _anims.find(name);
	if(i == _anims.end()) {
		// not found, don't do anything
	} else {
		// found it
		retval = i->second;
	}
	*/
	char x = name[0];
	char y = name[1];
	retval = _anims[x][y];
	return retval;
}
