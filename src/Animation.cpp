/* Animation.cpp
 *
 */

#include <vector>
#include "Animation.h"

Animation::Animation() {
}

Animation::~Animation() {
	for(celitr i = _cels.begin(); i != _cels.end(); i++) {
		delete *i;
	}
	_cels.clear();
}

void Animation::SetDelayInMsec(unsigned int ms) {
	_delayInMsec = ms;
}

void Animation::AddCel(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	Cel* cel = new Cel();
	cel->x = x;
	cel->y = y;
	cel->w = w;
	cel->h = h;
	_cels.push_back(cel);
}

unsigned int Animation::GetDelayInMsec() {
	return _delayInMsec;
}

Cel* Animation::GetCel(unsigned int idx) {
	Cel* retval = NULL;
	if(idx < GetCelCount()) {
		retval = _cels[idx];
	}
	return retval;
}

unsigned int Animation::GetCelCount() {
	return _cels.size();
}

int Animation::LoadTexture(const string& path) {
	// TODO: load the texture
	return -1;
}

int Animation::LoadScript(const string& path) {
	// TODO: this whole thing
	/* Example script:
	 * ---
	 *  Data/terra/terra.png
	 *  60
	 *  0,0,64,64
	 *  64,0,64,64
	 *  128,0,64,64
	 *  196,0,64,64
	 * ---
	 * First line is .png file of texture
	 * Second line is _delayInMsec
	 * Each subsequent line is a Cel definition
	 */
	return -1;
}
