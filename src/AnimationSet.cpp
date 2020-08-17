/* AnimationSet.cpp
 *
 */

#include <string>
#include <cassert>
#include "AnimationSet.h"

/*
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
*/

AnimType DecodeAnimType(char c) {
	AnimType retval = DEFAULT;
	switch(c) {
	case 'w':
		retval = WALK;
		break;
	case 'r':
		retval = RUN;
		break;
	case 'j':
		retval = JUMP;
		break;
	case 'a':
		retval = ATTACK;
		break;
	case 's':
		retval = SPEAK;
		break;
	case 't':
		retval = TAUNT;
		break;
	default:
		break;
	}
	return retval;
}

int DecodeModifier(char c) {
	int retval = -1;
	if(c >= 97 && c <= 122) {
		// lowercase
		retval = c - 97;
	} else if(c >=65 && c <= 90) {
		// uppercase
		retval = c - 65;
	}
	return retval;
}


AnimationSet::AnimationSet() {
	for(int i=0; i<ANIMTYPE_COUNT; ++i) {
		for(int j=0; j<26; ++j) {
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
	for(int i=0; i<ANIMTYPE_COUNT; ++i) {
		for(int j=0; j<26; ++j) {
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
	AnimType x = DecodeAnimType(name[0]);
	int y = DecodeModifier(name[1]);
	assert(y != -1);
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
	AnimType x = DecodeAnimType(name[0]);
	int y = DecodeModifier(name[1]);
	assert(y != -1);
	retval = _anims[x][y];
	return retval;
}
