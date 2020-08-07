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
}

Sprite::~Sprite() {
}

void Sprite::Tick() {
	double timeDelta = _celFlipDelta + (GetTimeInMsec() - GetLastTickEnd());
	double delay = static_cast<double>(_currentAnim->GetDelayInMsec());
	while(timeDelta > delay) {
		NextCel();
		timeDelta -= delay;
	}
	_celFlipDelta = timeDelta;
	/*
	if((GetTimeInMsec() - GetLastTickEnd()) >= _currentAnim->GetDelayInMsec()) {
#if defined DEBUGEXTRA
	Log(string("Sprite::Tick:  ") + to_string(GetTimeInMsec()) + " " + to_string(_currentAnim->GetDelayInMsec())
			+ " " + to_string(_currentCel) + " " + to_string(_celCount));
#endif //DEBUGEXTRA
		// time to switch frames
		NextCel();
	}
	*/
	Ticker::Tick();
}

void Sprite::NextCel() {
	++_currentCel;
	if(_currentCel >= _celCount) {
		// out of bounds, reset to zero
		_currentCel = 0;
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
	src->x = _currentAnim->GetCel(_currentCel)->x;
	src->y = _currentAnim->GetCel(_currentCel)->y;
	src->w = _currentAnim->GetCel(_currentCel)->w;
	src->h = _currentAnim->GetCel(_currentCel)->h;
}

void Sprite::GetDrawDstRect(DstRect* dst) {
	// set contents of dst to a rectangle around where this will be drawn on the screen
	unsigned int cx = _currentAnim->GetCel(_currentCel)->cx;
	unsigned int cy = _currentAnim->GetCel(_currentCel)->cy;
	unsigned int w = _currentAnim->GetCel(_currentCel)->w;
	unsigned int h = _currentAnim->GetCel(_currentCel)->h;
	dst->x = static_cast<int>(GetPositionX() - cx);
	dst->y = static_cast<int>(GetPositionY() - cy);
	dst->w = static_cast<int>(w);
	dst->h = static_cast<int>(h);
}

bool Sprite::SetAnimationSet(const string& name) {
	AnimationSet* aset = System::GetAnimationSet(name);
	if(aset) {
		_currentAset = aset;
		return SetAnimation("default");
	}
	return false;
}

bool Sprite::SetAnimation(const string& name) {
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
