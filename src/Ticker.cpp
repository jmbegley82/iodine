/* Ticker.cpp
 *
 */

#include "Ticker.h"
#include "Timing.h"

Ticker::Ticker() {
	//_lastTickStart = GetTimeInMsec();
	_lastTickEnd = GetTimeInMsec();
}

void Ticker::Tick() {
	_lastTickEnd = GetTimeInMsec();
}

double Ticker::GetLastTickEnd() {
	return _lastTickEnd;
}
