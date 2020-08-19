/* Motion.Test.cpp
 *
 */

#if defined DEBUG
#include <string>
#include "Motion.h"
#include "Logger.h"

using std::string;

int Motion::Test() {
	Motion* m = new Motion(); // create new Motion...
	m->SetPosition({100.0, 100.0}); // with position (100,100)
	coords c = m->GetPosition();
	char msg[128];
	char msgfmt[] = "Motion::Test:  m->GetPosition().x=%5.1f, .y=%5.1f";
	sprintf(msg, msgfmt, c.x, c.y);
	Logger(msg);	
	m->SetVelocity({1,-1}); // set velocity to (+1, -1)
	m->UpdatePosition(1);
	c = m->GetPosition();
	sprintf(msg, msgfmt, c.x, c.y);
	Logger(msg);	
	m->UpdatePosition(1);
	c = m->GetPosition();
	sprintf(msg, msgfmt, c.x, c.y);
	Logger(msg);	
	m->UpdatePosition(1);
	c = m->GetPosition();
	sprintf(msg, msgfmt, c.x, c.y);
	Logger(msg);	
	m->UpdatePosition(1);
	c = m->GetPosition();
	sprintf(msg, msgfmt, c.x, c.y);
	Logger(msg);	
	m->UpdatePosition(1);
	c = m->GetPosition();
	sprintf(msg, msgfmt, c.x, c.y);
	Logger(msg);	
	m->UpdatePosition(1);
	c = m->GetPosition();
	sprintf(msg, msgfmt, c.x, c.y);
	Logger(msg);	
	coords test = m->GetPosition();
	delete m;
	if(test.x == 106.0 && test.y == 94.0) {
		Logger("Motion::Test:  Test passed!");
		return 0;
	}
	sprintf(msg, "Motion::Test:  m->GetPosition().x=%5.1f, .y=%5.1f", test.x, test.y);
	Logger(msg);	
	Logger("Motion::Test:  Test failed!");
	return -1;
}
#endif //DEBUG
