/* ActionDemo.cpp
 *
 */

#include "ActionDemo.h"

void* Bouncer(Sprite* obj) {
	double posx = obj->GetPositionX();
	double posy = obj->GetPositionY();
	if(posx <= 0.0) {
		obj->SetVelocityX(1.0);
	} else if(posx >= 400.0) {
		obj->SetVelocityX(-1.0);
	}
	if(posy <= 0.0) {
		obj->SetVelocityY(1.0);
	} else if(posy >= 400.0) {
		obj->SetVelocityY(-1.0);
	}
	return NULL;
}
