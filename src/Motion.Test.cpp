/* Motion.Test.cpp
 *
 */

#if defined DEBUG
#include <string>
#include "Motion.h"
#include "Logger.h"

using std::string;

int Motion::Test() {
	Motion* m = new Motion({100,100}); // create new Motion with position (100,100)
	coords c = m->GetPosition();
	string msg = "Motion::Test:  m->GetVelocity().x=" + std::to_string(c.x) + ", .y=" + std::to_string(c.y);
	Logger(msg.c_str());
	m->SetVelocity({1,-1}); // set velocity to (+1, -1)
	m->UpdatePosition();
	c = m->GetPosition();
	msg = "Motion::Test:  m->GetVelocity().x=" + std::to_string(c.x) + ", .y=" + std::to_string(c.y);
	Logger(msg.c_str());
	m->UpdatePosition();
	c = m->GetPosition();
	msg = "Motion::Test:  m->GetVelocity().x=" + std::to_string(c.x) + ", .y=" + std::to_string(c.y);
	Logger(msg.c_str());
	m->UpdatePosition();
	c = m->GetPosition();
	msg = "Motion::Test:  m->GetVelocity().x=" + std::to_string(c.x) + ", .y=" + std::to_string(c.y);
	Logger(msg.c_str());
	m->UpdatePosition();
	c = m->GetPosition();
	msg = "Motion::Test:  m->GetVelocity().x=" + std::to_string(c.x) + ", .y=" + std::to_string(c.y);
	Logger(msg.c_str());
	m->UpdatePosition();
	c = m->GetPosition();
	msg = "Motion::Test:  m->GetVelocity().x=" + std::to_string(c.x) + ", .y=" + std::to_string(c.y);
	Logger(msg.c_str());
	m->UpdatePosition();
	c = m->GetPosition();
	msg = "Motion::Test:  m->GetVelocity().x=" + std::to_string(c.x) + ", .y=" + std::to_string(c.y);
	Logger(msg.c_str());
	coords test = m->GetPosition();
	delete m;
	if(test.x == 106.0 && test.y == 94.0) {
		Logger("Motion::Test:  Test passed!");
		return 0;
	}
	msg = "Motion::Test:  test.x=" + std::to_string(test.x) + ", .y=" + std::to_string(test.y);
	Logger(msg.c_str());
	Logger("Motion::Test:  Test failed!");
	return -1;
}
#endif //DEBUG
