/* Motion.h
 *
 */

#ifndef MOTION_H
#define MOTION_H

#include "Types.h"

//! This base class contains variables and functions related to being a moving object.
class Motion {
public:
	Motion();				//!< Initialize coordinates and velocity to zero
	Motion(coords val);			//!< Initialize with zero velocity and position specified by val
	void UpdatePosition();			//!< Update current position based on _velocity
	void SetPosition(coords val);		//!< Set position manually
	void SetPositionX(double val);		//!< Set X position manually
	void SetPositionY(double val);		//!< Set Y position manually
	void SetVelocity(coords val);		//!< Set velocity manually
	void SetVelocityX(double val);		//!< Set X velocity manually
	void SetVelocityY(double val);		//!< Set Y velocity manually
	coords GetPosition();			//!< Get struct containing X and Y coordinates
	double GetPositionX();			//!< Get double containing X coordinate
	double GetPositionY();			//!< Get double containing Y coordinate
	coords GetVelocity();			//!< Get struct containing X and Y velocities
	double GetVelocityX();			//!< Get double containing X velocity
	double GetVelocityY();			//!< Get double containing Y velocity
	coords PredictNextPosition();		//!< Calculate next position (collision notwithstanding)
	double PredictNextPositionX();		//!< Calculate next X position
	double PredictNextPositionY();		//!< Calculate next Y position
private:
	coords _position;			//!< Struct that contains x and y positional coordinates
	coords _velocity;			//!< Struct that contains x and y velocities
};

#endif //MOTION_H
