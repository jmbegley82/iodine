/* ActionDemo.cpp
 *
 */

#include "ActionDemo.h"

void Bouncer(Sprite* obj) {
	double posx = obj->GetPositionX();
	double posy = obj->GetPositionY();
	if(posx <= 0.0) {
		obj->SetVelocityX(0.25);
	} else if(posx >= 400.0) {
		obj->SetVelocityX(-0.25);
	}
	if(posy <= 0.0) {
		obj->SetVelocityY(0.25);
	} else if(posy >= 400.0) {
		obj->SetVelocityY(-0.25);
	}
}
