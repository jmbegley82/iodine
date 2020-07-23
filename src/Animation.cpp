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

using std::string;
using std::ifstream;

Animation::Animation() {
}

Animation::~Animation() {
	for(celitr i = _cels.begin(); i != _cels.end(); i++) {
		delete *i;
	}
	_cels.clear();
}

int Animation::AnmCommand(const string& cmd) {
	Sentence st(cmd);
	/* valid syntax:
	 * texture=Data/whatnot.png
	 * delay = 60
	 * cel = 0,0,64,64
	 * cel += 64,0,64,64
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
			AddCel(cs.x, cs.y, cs.w, cs.h);
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
			return 0;
		}
	}
	return -1;
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
	 *  texture=Data/terra/terra.png
	 *  delay=60
	 *  cel+=0,0,64,64
	 *  cel+=64,0,64,64
	 *  cel+=128,0,64,64
	 *  cel+=196,0,64,64
	 * ---
	 * First line is .png file of texture
	 * Second line is _delayInMsec
	 * Each subsequent line is a Cel definition
	 */
	string line;
	ifstream file(path);
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
