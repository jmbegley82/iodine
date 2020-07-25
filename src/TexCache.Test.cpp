/* TexCache.Test.cpp
 *
 */

#if defined DEBUG

#include "TexCache.h"
#include "GfxTypes.h"
#include "Logger.h"

int TexCache::Test() {
	Texture* test1 = TexCache::Load("data/june.png");
	Texture* test2 = TexCache::Load("data/august.png");
	Texture* test3 = TexCache::Load("data/december.png");
	Texture* test4 = TexCache::Load("data/june.png");
	return 0;
}

#endif //DEBUG
