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
#include "Motion.h"
#include "Types.h"

using std::string;

int main(int argc, char** argv) {
	Logger_init();
	Logger("main entered.");

#if defined DEBUG
	Atom::Test();
	Logger_Test();
	Timing_Test();
	Ticker::Test();
	Motion::Test();
#endif //DEBUG

	Logger("that's about enough for today.");
	Logger_finish();
	return 0;
}
