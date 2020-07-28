/* TexCache.Test.cpp
 *
 */

#if defined DEBUG

#include <cassert>
#include "TexCache.h"
#include "GfxTypes.h"
#include "Logger.h"

int TexCache::Test() {
	TexCache* tex = new TexCache();
	Texture* test1 = tex->Load("data/june.png");
	Texture* test2 = tex->Load("data/august.png");
	Texture* test3 = tex->Load("data/december.png");
	bool test4 = tex->Unload("data/december.png");
	Texture* test5 = tex->Load("data/june.png");
	assert(*test1 == *test5);
	assert(test1 == test5);
	assert(test4);
	Log("TexCache::Test:  Passed!");
	delete tex;
	return 0;
}

#endif //DEBUG
