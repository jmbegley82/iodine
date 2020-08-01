/* Animation.Test.cpp
 *
 */

#if defined DEBUG

#include <cstdio>
#include <cassert>
#include "Animation.h"
#include "Logger.h"

int Animation::Test() {
	Animation* anim = new Animation();
	anim->LoadScript("data/test.anm");
	char msg[128];
	sprintf(msg, "Animation::Test:  GetCelCount=%d, GetDelayInMsec=%d", anim->GetCelCount(), anim->GetDelayInMsec());
	Logger(msg);
	unsigned int test1 = anim->GetCel(2)->x;
	sprintf(msg, "Animation::Test:  test1=%d, which is hopefully 128", test1);
	Logger(msg);
	assert(test1 == 128);
	assert(anim->GetCelCount() == 4);
	assert(anim->GetDelayInMsec() == 100);
	delete anim;
	return 0;
}

#endif //DEBUG
