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
#include "Geometry.h"
#include "Types.h"
#include "Platform.h"

using std::string;

int main(int argc, char** argv) {
	Logger_init();
	Logger("main entered.");

#if defined DEBUG
#if defined DEBUGATOM
	Atom::Test();
#endif //DEBUGATOM
#if defined DEBUGLOGGER
	Logger_Test();
#endif //DEBUGLOGGER
#if defined DEBUGTIMING
	Timing_Test();
#endif //DEBUGTIMING
#if defined DEBUGTICKER
	Ticker::Test();
#endif //DEBUGTICKER
#if defined DEBUGMOTION
	Motion::Test();
#endif //DEBUGMOTION
#if defined DEBUGGEOMETRY
	Geometry::Test();
#endif //DEBUGGEOMETRY
#if defined DEBUGPLATFORM
	Platform_Test();
#endif //DEBUGPLATFORM
#endif //DEBUG

	Logger("that's about enough for today.");
	Logger_finish();
	return 0;
}
