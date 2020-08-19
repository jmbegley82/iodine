/* Motion.cpp
 *
 */

#include "Motion.h"

Motion::Motion() {
	SetVelocity({0.0, 0.0});
}

void Motion::UpdatePosition(double ms) {
	SetPosition(PredictNextPosition(ms));
}

void Motion::SetVelocity(coords val) {
	SetVelocityX(val.x);
	SetVelocityY(val.y);
}

void Motion::SetVelocityX(double val) {
	_velocity.x = val;
}

void Motion::SetVelocityY(double val) {
	_velocity.y = val;
}

coords Motion::GetVelocity() {
	return _velocity;
}

double Motion::GetVelocityX() {
	return _velocity.x;
}

double Motion::GetVelocityY() {
	return _velocity.y;
}

coords Motion::PredictNextPosition(double ms) {
	coords retval;
	retval.x = PredictNextPositionX(ms);
	retval.y = PredictNextPositionY(ms);
	return retval;
}

double Motion::PredictNextPositionX(double ms) {
	return GetPositionX() + (GetVelocityX() * ms);
}

double Motion::PredictNextPositionY(double ms) {
	return GetPositionY() + (GetVelocityY() * ms);
}

double* Motion::GetVelocityXPtr() {
	return &_velocity.x;
}

double* Motion::GetVelocityYPtr() {
	return &_velocity.y;
}
