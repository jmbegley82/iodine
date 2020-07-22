/* AnimationSet.Test.cpp
 *
 */

#if defined DEBUG

#include <string>
#include <cstring>
#include <cassert>
#include "AnimationSet.h"
#include "Animation.h"
#include "Cel.h"
#include "Logger.h"

int AnimationSet::Test() {
	AnimationSet* aset = new AnimationSet();

	Animation* anim = aset->GetAnimation("walkl");
	anim->LoadTexture("terra/terra.png");
	anim->SetDelayInMsec(100);
	anim->AddCel(  0, 0, 64, 64);
	anim->AddCel( 64, 0, 64, 64);
	anim->AddCel(128, 0, 64, 64);
	anim->AddCel(192, 0, 64, 64);

	anim = aset->GetAnimation("walkr");
	anim->LoadTexture("terra/terra.png");
	anim->SetDelayInMsec(100);
	anim->AddCel(  0, 0, 64, 64);
	anim->AddCel( 64, 0, 64, 64);
	anim->AddCel(128, 0, 64, 64);
	anim->AddCel(192, 0, 64, 64);

	anim = aset->GetAnimation("explode");
	anim->LoadTexture("fx/explosion1.png");
	anim->SetDelayInMsec(60);
	anim->AddCel(  0, 0, 128, 128);
	anim->AddCel(128, 0, 128, 128);
	anim->AddCel(256, 0, 128, 128);
	anim->AddCel(384, 0, 128, 128);
	anim->AddCel(512, 0, 128, 128);
	anim->AddCel(640, 0, 128, 128);
	anim->AddCel(768, 0, 128, 128);
	anim->AddCel(896, 0, 128, 128);

	int test1 = aset->GetAnimation("walkl")->GetCelCount();  //4
	int test2 = aset->GetAnimation("walkr")->GetCel(3)->x;   //192
	int test3 = aset->GetAnimation("explode")->GetCelCount();//8
	int test4 = aset->GetAnimation("explode")->GetCel(7)->x; //896

	assert(test1 == 4);
	assert(test2 == 192);
	assert(test3 == 8);
	assert(test4 == 896);

	char msg[128];
	sprintf(msg, "AnimationSet::Test:  passed!");
	Logger(msg);
	delete aset;
	return 0;
}

#endif //DEBUG
