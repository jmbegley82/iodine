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
	/*
	anim->LoadTexture("somesuch.png");
	anim->SetDelayInMsec(100);
	anim->AddCel(  0,  0, 64, 64);
	anim->AddCel( 64,  0, 64, 64);
	anim->AddCel(128,  0, 64, 64);
	anim->AddCel(192,  0, 64, 64);
	*/
	assert(anim->AnmCommand("texture=Data/somesuch.png") == 0);
	assert(anim->AnmCommand("delay=100") == 0);
	assert(anim->AnmCommand("cel+=0,0,64,64") == 0);
	assert(anim->AnmCommand("cel+=64,0,64,64") == 0);
	assert(anim->AnmCommand("cel+=128,0,64,64") == 0);
	assert(anim->AnmCommand("cel+=192,0,64,64") == 0);
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
