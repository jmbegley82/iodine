/* TexCache.Test.cpp
 *
 */

#if defined DEBUG

#include <cassert>
#include "TexCache.h"
#include "GfxTypes.h"
#include "Logger.h"

int TexCache::Test() {
	Texture* test1 = TexCache::Load("data/june.png");
	Texture* test2 = TexCache::Load("data/august.png");
	Texture* test3 = TexCache::Load("data/december.png");
	bool test4 = TexCache::Unload("data/december.png");
	Texture* test5 = TexCache::Load("data/june.png");
	assert(*test1 == *test5);
	assert(test4);
	Log("TexCache::Test:  Passed!");
	return 0;
}

#endif //DEBUG
