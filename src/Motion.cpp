/* Motion.cpp
 *
 */

#include "Motion.h"

Motion::Motion() {
	SetPosition({0.0, 0.0});
	SetVelocity({0.0, 0.0});
}

Motion::Motion(coords val) {
	SetPosition(val);
	SetVelocity({0.0, 0.0});
}

void Motion::UpdatePosition() {
	SetPosition(PredictNextPosition());
}

void Motion::SetPosition(coords val) {
	SetPositionX(val.x);
	SetPositionY(val.y);
}

void Motion::SetPositionX(double val) {
	_position.x = val;
}

void Motion::SetPositionY(double val) {
	_position.y = val;
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

coords Motion::GetPosition() {
	return _position;
}

double Motion::GetPositionX() {
	return _position.x;
}

double Motion::GetPositionY() {
	return _position.y;
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

coords Motion::PredictNextPosition() {
	coords retval;
	retval.x = PredictNextPositionX();
	retval.y = PredictNextPositionY();
	return retval;
}

double Motion::PredictNextPositionX() {
	return GetPositionX() + GetVelocityX();
}

double Motion::PredictNextPositionY() {
	return GetPositionY() + GetVelocityY();
}

