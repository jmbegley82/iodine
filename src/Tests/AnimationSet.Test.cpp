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
	aset->LoadAnimation("walkl", "data/terra.walkl.anm");
	aset->LoadAnimation("walkr", "data/terra.walkr.anm");
	aset->LoadAnimation("explode", "data/explosion.anm");

	int test1 = aset->FindAnimation("walkl")->GetCelCount();  //4
	int test2 = aset->FindAnimation("walkr")->GetCel(3)->x;   //192
	int test3 = aset->FindAnimation("explode")->GetCelCount();//8
	int test4 = aset->FindAnimation("explode")->GetCel(7)->x; //896

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
