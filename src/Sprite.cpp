/* Sprite.cpp
 *
 */

#include "Sprite.h"
#include "System.h"
#include "Timing.h"

#if defined DEBUGEXTRA
#include "Logger.h"
using std::string;
using std::to_string;
#endif //DEBUGEXTRA

Sprite::Sprite() {
	_celFlipDelta = 0;
	_isOneshot = false;
	_hasExpired = false;
	for(int i=0; i<MAX_ACTIONS; ++i) {
		_actions[i] = NULL;
	}
	//_actions = NULL;
}

Sprite::~Sprite() {
}

void Sprite::Tick() {
	// timeDelta = time elapsed since last Tick
	double timeDelta = _celFlipDelta + (GetTimeInMsec() - GetLastTickEnd());
	// update Animation
	double delay = static_cast<double>(_currentAnim->GetDelayInMsec());
	while(timeDelta > delay) {
		NextCel();
		timeDelta -= delay;
	}
	_celFlipDelta = timeDelta;
	// do actions
	//if(_actions) _actions(this);
	for(int i=0; i<MAX_ACTIONS; ++i) {
		if(_actions[i] != NULL) {
			_actions[i](this);
		}
	}
	// update position
	UpdatePosition(GetTimeInMsec() - GetLastTickEnd());
	// update last tick time
	Ticker::Tick();
}

void Sprite::NextCel() {
	++_currentCel;
	if(_currentCel >= _celCount) {
		// out of bounds, reset to zero
		_currentCel = 0;
		if(_isOneshot) {
			_hasExpired = true;
		}
	}
}

Texture* Sprite::GetTexture() {
	Texture* retval = NULL;
	if(_currentAnim)
		retval = _currentAnim->GetTexture();
	return retval;
}

void Sprite::GetDrawSrcRect(SrcRect* src) {
	// set contents of src to a rectangle around our current Animation's current Cel
	// alternatively, set it to something that won't cause a crash if executed
	Cel* thisCel = _currentAnim->GetCel(_currentCel);
	src->x = thisCel->x;
	src->y = thisCel->y;
	src->w = thisCel->w;
	src->h = thisCel->h;
}

void Sprite::GetDrawDstRect(DstRect* dst) {
	// set contents of dst to a rectangle around where this will be drawn on the screen
	Cel* thisCel = _currentAnim->GetCel(_currentCel);
	unsigned int cx = thisCel->cx;
	unsigned int cy = thisCel->cy;
	unsigned int w = thisCel->w;
	unsigned int h = thisCel->h;
	dst->x = static_cast<int>(GetPositionX() - cx);
	dst->y = static_cast<int>(GetPositionY() - cy);
	dst->w = static_cast<int>(w);
	dst->h = static_cast<int>(h);
}

bool Sprite::SetAnimationSet(const string& name) {
	AnimationSet* aset = System::GetAnimationSet(name);
	if(aset) {
		_currentAset = aset;
		return SetAnimation("de");
	}
	return false;
}

bool Sprite::SetAnimation(const char* name) {
	if(_currentAset) {
		Animation* anm = _currentAset->FindAnimation(name);
		if(anm) {
			_currentAnim = anm;
			_currentCel = 0;
			_celCount = anm->GetCelCount();
			return true;
		}
	}
	return false;
}

void Sprite::SetOneshot() {
	_isOneshot = true;
}

bool Sprite::IsOneshot() {
	return _isOneshot;
}

bool Sprite::HasExpired() {
	return _hasExpired;
}

#if defined DEBUG

#include "ActionDemo.h"
void Sprite::MakeBouncy() {
	_actions[0] = Bouncer;
}

#endif //DEBUG
