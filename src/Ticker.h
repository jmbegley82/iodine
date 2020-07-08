/* Ticker.h
 *
 */

#ifndef TICKER_H
#define TICKER_H

//! A base class containing time-awareness related code
class Ticker {
public:
	Ticker();			//!< @brief Set _lastTickEnd now so it's something other than zero
	virtual void Tick();		//!< @brief Sets _lastTickEnd to the current time in msec
					//!< @details Make sure to call this at the end of any inheriting class's Tick!
	double GetLastTickEnd();	//!< @brief Get timestamp saved at the end of the last call to Tick()
					//!< @details Unless it hasn't been ticked yet; then the time at the end of construction.
private:
	double _lastTickEnd;
};

#endif //TICKER_H
