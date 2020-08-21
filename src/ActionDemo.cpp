/* ActionDemo.cpp
 *
 */

#include "ActionDemo.h"

void Bouncer(Sprite* obj) {
	double posx = obj->GetPositionX();
	double posy = obj->GetPositionY();
	if(posx <= 0.0) {
		obj->SetVelocityX(0.125);
	} else if(posx >= 400.0) {
		obj->SetVelocityX(-0.125);
	}
	if(posy <= 0.0) {
		obj->SetVelocityY(0.125);
	} else if(posy >= 400.0) {
		obj->SetVelocityY(-0.125);
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
	double newvx = prevvx;
	double newvy = prevvy;
	VControl* p1 = System::GetP1VControl();

	if(p1->Left) {
		newvx += -0.02;
	} else if(p1->Right) {
		newvx += +0.02;
	} else {
		newvx = newvx * 0.875;
	}

	if(p1->Up) {
		newvy += -0.02;
	} else if(p1->Down) {
		newvy += +0.02;
	} else {
		newvy = newvy * 0.875;
	}

	if(newvx > 0.5) {
		newvx = 0.5;
	} else if(newvx < -0.5) {
		newvx = -0.5;
	}

	if(newvy > 0.5) {
		newvy = 0.5;
	} else if(newvy < -0.5) {
		newvy = -0.5;
	}


	if(prevvx != newvx)
		obj->SetVelocityX(newvx);
	if(prevvy != newvy)
		obj->SetVelocityY(newvy);
}
