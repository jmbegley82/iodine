/* Sprite.cpp
 *
 */

#include "Sprite.h"

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
	if(_currentanim)
		retval = _currentAnim->GetTexture();
	return retval;
}

void Sprite::GetDrawSrcRect(SrcRect* src) {
	// set contents of src to a rectangle around our current Animation's current Cel
	// alternatively, set it to something that won't cause a crash if executed
	
}

void Sprite::GetDrawDstRect(DstRect* dst) {
	// set contents of dst to a rectangle around where this will be drawn on the screen
	dst->x = static_cast<int>(_position.x - _center.x);
	dst->y = static_cast<int>(_position.y - _center.y);
	dst->w = static_cast<int>(_size.w);
	dst->h = static_cast<int>(_size.h);
}

bool Sprite::SetAnimationSet(const string& name) {
	
	return false;
}

bool Sprite::SetAnimation(const string& name) {
	if(_currentASet) {
		Animation* anm = _currentASet->FindAnimation(name);
		if(anm) {
			_currentAnim = anm;
			_currentCel = 0;
			_celCount = anm->GetCelCount();
			return true;
		}
	}
	return false;
}
