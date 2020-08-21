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

void ExpireAtEdge(Sprite* obj) {
	double posx = obj->GetPositionX();
	double posy = obj->GetPositionY();
	if(posx <= 0.0 || posx >= 400.0 || posy <= 0.0 || posy >= 400.0) {
		obj->Expire();
	}
}

#include "System.h"

void DbgControl(Sprite* obj) {
	double prevvx = obj->GetVelocityX();
	double prevvy = obj->GetVelocityY();
	double newvx = 0.0;
	double newvy = 0.0;
	VControl* p1 = System::GetP1VControl();

	if(p1->Left) {
		newvx = -0.2;
	} else if(p1->Right) {
		newvx = +0.2;
	}

	if(p1->Up) {
		newvy = -0.2;
	} else if(p1->Down) {
		newvy = +0.2;
	}

	if(prevvx != newvx)
		obj->SetVelocityX(newvx);
	if(prevvy != newvy)
		obj->SetVelocityY(newvy);
}
