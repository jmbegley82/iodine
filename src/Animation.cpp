/* Animation.cpp
 *
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Animation.h"
#include "CelString.h"
#include "Sentence.h"
#include "StringManip.h"
#include "System.h"
#include "Filesystem.h"
#include "GfxTypes.h"

using std::string;
using std::ifstream;

Animation::Animation() {
    _texture = NULL;
    _delayInMsec = 100;
}

Animation::~Animation() {
	for(celitr i = _cels.begin(); i != _cels.end(); ++i) {
		delete *i;
	}
	_cels.clear();
}

int Animation::AnmCommand(const string& cmd) {
	Sentence st(cmd);
	/* valid syntax:
	 * texture=Data/whatnot.png
	 * delay = 60
	 * cel = 0,0,64,64,32,32
	 * cel += 64,0,64,64,32,32
	 */

	// declarator presence indicates an error condition here
	if(st.declarator != "") {
		return -1;
	}

	if(st.subject == "" || st.op == "" || st.target == "") {
		return -1;  // none of those things should be empty!
	}

	if(st.subject == "cel") {
		// target hopefully contains three commas separating four positive integers
		// op should be +=
		CelString cs(st.target);
		if(st.op == "+=" && cs.isValid) {
			AddCel(cs.x, cs.y, cs.w, cs.h, cs.cx, cs.cy);
			return 0;
		}
	} else if (st.subject == "delay") {
		// target should be a positive integer
		// op should be =
		if(ContainsNumericData(st.target) && st.op == "=") {
			int rval = std::stoi(st.target);
			if(rval > 0) {
				SetDelayInMsec(rval);
				return 0;
			}
		}
	} else if (st.subject == "texture") {
		// target should be a relative path (eg. "Data/texture.png")
		// op should be =
		// eg. TextureCache::LoadTexture(st.target) which doesn't exist yet
		if(st.op == "=") {
			if(LoadTexture(st.target)) {
				return 0;
			}
		}
	}
	return -1;
}

void Animation::SetDelayInMsec(unsigned int ms) {
	_delayInMsec = ms;
}

void Animation::AddCel(unsigned int x, unsigned int y, unsigned int w, unsigned int h,
						unsigned int cx, unsigned int cy) {
	Cel* cel = new Cel();
	cel->x = x;
	cel->y = y;
	cel->w = w;
	cel->h = h;
	cel->cx = cx;
	cel->cy = cy;
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

bool Animation::LoadTexture(const string& path) {
	// TODO: load the texture
	Texture* tex = System::LoadTexture(path);
	if(tex) {
		_texture = tex;
		return true;
	}
	return false;
}

Texture* Animation::GetTexture() {
	return _texture;
}

int Animation::LoadScript(const string& path) {
	/* Example script:
	 * ---
	 *  texture=data/terra/terra.png
	 *  delay=60
	 *  cel+=0,0,64,64,32,32
	 *  cel+=64,0,64,64,32,32
	 *  cel+=128,0,64,64,32,32
	 *  cel+=196,0,64,64,32,32
	 * ---
	 * First line is .png file of texture
	 * Second line is _delayInMsec
	 * Each subsequent line is a Cel definition
	 */
	string line;
	ifstream file(string(GetInstallDir()) + "/" + path);
	if(file.is_open()) {
		while(getline(file, line)) {
			// do something with line
			AnmCommand(line);
		}
		file.close();
	} else {
		// file not found
	}
	return -1;
}
