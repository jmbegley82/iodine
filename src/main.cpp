/* main.cpp
 * Iodine tests
 *
 */

#include <pthread.h>
#include <string>
#include "Logger.h"
#include "Atom.h"
#include "Timing.h"
#include "Ticker.h"

using std::string;

void test_basics() {
	Logger("a = new Atom() -- create a regular, self-naming Atom.");
	Atom* a = new Atom();
	string id = a->GetIdentity();
	string msg = "a->GetIdentity() returned: \"" + id + "\".";
	Logger(msg.c_str());
	Logger("deleting a...");
	delete a;
	Logger("b = new Atom(\"fancyname\") -- create an Atom with the identity \"fancyname\"");
	Atom* b = new Atom("fancyname");
	id = b->GetIdentity();
	msg = "b->GetIdentity() returned: \"" + id + "\".";
	Logger(msg.c_str());

	int rv = b->Command("gibberish");
	msg = "b->Command was fed gibberish and emitted the following: " + Atom::RetvalStr(rv);
	Logger(msg.c_str());
	Logger("CMD_ERROR was the expected response.");

	rv = b->Command("test-bypass");
	msg = "b->Command was fed test-bypass and emitted the following: " + Atom::RetvalStr(rv);
	Logger(msg.c_str());
	Logger("CMD_INVALID was the expected response.");

	rv = b->Command("test");
	msg = "b->Command was fed test and emitted the following: " + Atom::RetvalStr(rv);
	Logger(msg.c_str());
	Logger("CMD_SUCCESS was the expected response.");

	Logger("Let's go ahead and manually flush _logbuffer while we're here");
	Logger_process();

	Logger("deleting b...");
	delete b;
}

void* test_logger_thread(void *arg) {
	int reps = 100000;  // set to # of desired iterations
	string tname = std::to_string((long int)arg);
	for(int i=0; i<reps; i++) {
		string currentRep = std::to_string(i);
		string msg = "Thread#" + tname + ":  Bombardment#" + currentRep;
		Logger(msg.c_str());
	}
	pthread_exit((void*)0);
}

void test_logger() {
	int threadcount = 7;  // set to # of desired concurrent testing threads
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_t threads[threadcount];
	for(int i=0; i<threadcount; i++) {
		pthread_create(&threads[i], &attr, test_logger_thread, (void*)(long int)i);
	}
	pthread_attr_destroy(&attr);
	// wait for threads to end
	void* status;
	for(int i=0; i<threadcount; i++) {
		pthread_join(threads[i], &status);
	}
}

void test_timing() {
	string msg = "";
	Logger_pause();
	Logger_now("There should be one second between the next few lines that are printed.");
	SleepMsec(1000);
	msg = "GetTimeInMsec:" + std::to_string(GetTimeInMsec());
	Logger_now(msg.c_str());
	SleepMsec(1000);
	msg = "GetTimeInMsec:" + std::to_string(GetTimeInMsec());
	Logger_now(msg.c_str());
	SleepUsec(1000000);
	msg = "GetTimeInMsec:" + std::to_string(GetTimeInMsec());
	Logger_now(msg.c_str());
	SleepMsec(1000);
	msg = "GetTimeInMsec:" + std::to_string(GetTimeInMsec());
	Logger_now(msg.c_str());
	SleepUsec(1000000);
	msg = "GetTimeInMsec:" + std::to_string(GetTimeInMsec());
	Logger_now(msg.c_str());
	SleepMsec(1000);
	msg = "GetTimeInUsec:" + std::to_string(GetTimeInUsec());
	Logger(msg.c_str());
	msg = "GetTimeInMsec:" + std::to_string(GetTimeInMsec());
	Logger_now(msg.c_str());
	Logger_unpause();
}

void test_ticker() {
	Atom* a = new Atom("a");
	string msg = "a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger_now(msg.c_str());
	SleepMsec(1000);
	a->Tick();
	msg = "a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger_now(msg.c_str());
	SleepMsec(1000);
	a->Tick();
	msg = "a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger_now(msg.c_str());
	SleepMsec(1000);
	a->Tick();
	msg = "a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger_now(msg.c_str());
	SleepMsec(1000);
	a->Tick();
	msg = "a->GetLastTickEnd() = " + std::to_string(a->GetLastTickEnd());
	Logger_now(msg.c_str());
	SleepMsec(1000);
	a->Tick();
	delete a;
}

int main(int argc, char** argv) {
	Logger_init();
	Logger("main entered.");

	test_basics();
	//test_logger();
	test_timing();
	test_ticker();
	// end

	Logger("that's about enough for today.");
	Logger_finish();
	return 0;
}
