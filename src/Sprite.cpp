/* Sprite.cpp
 *
 */

#include "Sprite.h"
#include "System.h"

Sprite::Sprite() {
}

Sprite::~Sprite() {
}

void Sprite::Tick() {
	// do things
	Ticker::Tick();
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
	// here have some hardcoded data:
	src->x = 0;
	src->y = 0;
	src->w = 432;
	src->h = 394;
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
