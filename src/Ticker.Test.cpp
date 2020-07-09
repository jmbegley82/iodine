/* Ticker.Test.cpp
 *
 */

#if defined DEBUG

#include <string>
#include "Ticker.h"
#include "Timing.h"
#include "Atom.h"
#include "Logger.h"

using std::string;

int Ticker::Test() {
	Atom* a = new Atom("a");
	string msg = "Ticker::Test:  a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger(msg.c_str());
	Logger_setflushdelay(60);
	SleepMsec(1000);
	a->Tick();
	msg = "Ticker::Test:  a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger(msg.c_str());
	Logger_setflushdelay(120);
	SleepMsec(1000);
	a->Tick();
	msg = "Ticker::Test:  a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger(msg.c_str());
	Logger_setflushdelay(240);
	SleepMsec(1000);
	a->Tick();
	msg = "Ticker::Test:  a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger(msg.c_str());
	Logger_setflushdelay(480);
	SleepMsec(1000);
	a->Tick();
	msg = "Ticker::Test:  a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger(msg.c_str());
	Logger_setflushdelay(960);
	SleepMsec(1000);
	a->Tick();
	delete a;
	Logger_setflushdelay(60);
	return 0;
}

#endif //DEBUG
