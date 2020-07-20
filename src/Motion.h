/* Motion.h
 *
 */

#if !defined MOTION_H
#define MOTION_H

#include "Geometry.h"
#include "Types.h"

//! This base class contains variables and functions related to being a moving object.
class Motion : public Geometry {
public:
	Motion();				//!< Initialize coordinates and velocity to zero
	void UpdatePosition();			//!< Update current position based on _velocity
	void SetVelocity(coords val);		//!< Set velocity manually
	void SetVelocityX(double val);		//!< Set X velocity manually
	void SetVelocityY(double val);		//!< Set Y velocity manually
	coords GetVelocity();			//!< Get struct containing X and Y velocities
	double GetVelocityX();			//!< Get double containing X velocity
	double GetVelocityY();			//!< Get double containing Y velocity
	coords PredictNextPosition();		//!< Calculate next position (collision notwithstanding)
	double PredictNextPositionX();		//!< Calculate next X position
	double PredictNextPositionY();		//!< Calculate next Y position
#if defined DEBUG
	static int Test();			//!< Run internal tests
#endif //DEBUG
protected:
	double* GetVelocityXPtr();
	double* GetVelocityYPtr();
private:
	coords _velocity;			//!< Struct that contains x and y velocities
};

#endif //MOTION_H
