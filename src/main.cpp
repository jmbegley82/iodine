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
#include "Container.h"
#include "Var.h"
#include "VarSet.h"
#include "Types.h"
#include "Platform.h"
#include "StringManip.h"
#include "Introspector.h"
#include "Sentence.h"
#include "Animation.h"
#include "AnimationSet.h"
#include "CelString.h"

using std::string;

int main(int argc, char** argv) {
	Logger("main entered.");

#if defined DEBUG
#if defined DEBUGATOM
	Atom::Test();
#endif //DEBUGATOM
#if defined DEBUGLOGGER
	Logger_Test();
	LogCxxTest();
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
#if defined DEBUGCONTAINER
	Container::Test();
#endif //DEBUGCONTAINER
#if defined DEBUGVAR
	Var::Test();
#endif //DEBUGVAR
#if defined DEBUGVARSET
	VarSet::Test();
#endif //DEBUGVARSET
#if defined DEBUGSMANIP
	StringManip_Test();
#endif //DEBUGSMANIP
#if defined DEBUGINTROSPECTOR
	Introspector::Test();
#endif //DEBUGINTROSPECTOR
#if defined DEBUGSENTENCE
	Sentence::Test();
#endif //DEBUGSENTENCE
#if defined DEBUGANIMATION
	Animation::Test();
#endif //DEBUGANIMATION
#if defined DEBUGANIMATIONSET
	AnimationSet::Test();
#endif //DEBUGANIMATIONSET
	CelString::Test();
#endif //DEBUG
	Logger("that's about enough for today.");
	//Logger_finish();
	return 0;
}
