/* TexCache.Test.cpp
 *
 */

#if defined DEBUG

#include <cassert>
#include "TexCache.h"
#include "GfxTypes.h"
#include "Logger.h"

int TexCache::Test() {
	// these tests should work whether the named files exist or not
	TexCache* tex = new TexCache();
	Texture* test1 = tex->Load("data/june.png");
	Texture* test2 = tex->Load("data/august.png");
	Texture* test3 = tex->Load("data/december.png");
	bool test4 = tex->Unload("data/december.png");
	Texture* test5 = tex->Load("data/june.png");
	//assert(*test1 == *test5);  //only makes sense with double placeholder in GfxTypes!
	assert(test1 == test5);
	assert(test4);
	// these tests, however, will require the named files.
	Texture* terra = tex->Load("data/terra.png");
	unsigned int fmt = 0;
	int access = 0;
	int wid = 0;
	int hgt = 0;
	int test6 = SDL_QueryTexture(terra, &fmt, &access, &wid, &hgt);
	Log("TexCache::Test:  Data:  " + std::to_string(wid) + " " + std::to_string(hgt));
	Log("TexCache::Test:  Passed!");
	delete tex;
	return 0;
}

#endif //DEBUG
