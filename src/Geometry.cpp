/* Geometry.cpp
 *
 */

#include "Geometry.h"
#include "Types.h"

Geometry::Geometry() {
	SetPosition({0,0});
	SetSize({0,0});
	SetCenter({0,0});
}

Geometry::Geometry(coords val) {
	SetPosition(val);
	SetSize({0,0});
	SetCenter({0,0});
}

void Geometry::SetPosition(coords val) {
	SetPositionX(val.x);
	SetPositionY(val.y);
}

void Geometry::SetPositionX(double val) {
	_position.x = val;
}

void Geometry::SetPositionY(double val) {
	_position.y = val;
}

void Geometry::SetSize(coords val) {
	SetSizeW(val.x);
	SetSizeH(val.y);
}

void Geometry::SetSizeW(double val) {
	if(val >= 0) _size.x = val;
}

void Geometry::SetSizeH(double val) {
	if(val >= 0) _size.y = val;
}

void Geometry::SetCenter(coords val) {
	SetCenterX(val.x);
	SetCenterY(val.y);
}

void Geometry::SetCenterX(double val) {
	_center.x = val;
}

void Geometry::SetCenterY(double val) {
	_center.y = val;
}

coords Geometry::GetPosition() {
	return _position;
}

double Geometry::GetPositionX() {
	return _position.x;
}

double Geometry::GetPositionY() {
	return _position.y;
}


coords Geometry::GetSize() {
	return _size;
}

double Geometry::GetSizeW() {
	return _size.x;
}

double Geometry::GetSizeH() {
	return _size.y;
}

coords Geometry::GetCenter() {
	return _center;
}

double Geometry::GetCenterX() {
	return _center.x;
}

double Geometry::GetCenterY() {
	return _center.y;
}

double Geometry::GetXLeft() {
	return GetPositionX() + GetCenterX();
}

double Geometry::GetXRight() {
	return GetPositionX() + GetCenterX() + GetSizeW();
}

double Geometry::GetYTop() {
	return GetPositionY() + GetCenterY();
}

double Geometry::GetYBottom() {
	return GetPositionY() + GetCenterY() + GetSizeH();
}

coords Geometry::GetTopLeft() {
	return {GetXLeft(), GetYTop()};
}

coords Geometry::GetTopRight() {
	return {GetXRight(), GetYTop()};
}

coords Geometry::GetBottomLeft() {
	return {GetXLeft(), GetYBottom()};
}

coords Geometry::GetBottomRight() {
	return {GetXRight(), GetYBottom()};
}
