/* Geometry.h
 *
 */

#if !defined GEOMETRY_H
#define GEOMETRY_H

#include "Types.h"

class Geometry {
public:
	Geometry();
	Geometry(coords val);
	void SetPosition(coords val);		//!< Set position manually
	void SetPositionX(double val);		//!< Set X position manually
	void SetPositionY(double val);		//!< Set Y position manually
	void SetSize(coords val);
	void SetSizeW(double val);
	void SetSizeH(double val);
	void SetCenter(coords val);
	void SetCenterX(double val);
	void SetCenterY(double val);
	coords GetPosition();			//!< Get struct containing X and Y coordinates
	double GetPositionX();			//!< Get double containing X coordinate
	double GetPositionY();			//!< Get double containing Y coordinate
	coords GetSize();
	double GetSizeW();
	double GetSizeH();
	coords GetCenter();
	double GetCenterX();
	double GetCenterY();
#if defined DEBUG
	int Test();
#endif //DEBUG
private:
	coords _position;			//!< Struct that contains x and y positional coordinates
	coords _size;
	coords _center;
};

#endif //GEOMETRY_H
