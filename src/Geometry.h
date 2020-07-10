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
	void SetSize(coords val);		//!< Set size manually
	void SetSizeW(double val);		//!< Set size width
	void SetSizeH(double val);		//!< Set size height
	void SetCenter(coords val);		//!< Set center offset
	void SetCenterX(double val);		//!< Set center offset X
	void SetCenterY(double val);		//!< Set center offset Y
	coords GetPosition();			//!< Get struct containing X and Y coordinates
	double GetPositionX();			//!< Get double containing X coordinate
	double GetPositionY();			//!< Get double containing Y coordinate
	coords GetSize();			//!< Get struct containing size
	double GetSizeW();			//!< Get size width
	double GetSizeH();			//!< Get size height
	coords GetCenter();			//!< Get struct containing center offset
	double GetCenterX();			//!< Get center offset X value
	double GetCenterY();			//!< Get center offset Y value
	// bounding box:
	double GetXLeft();			//!< Get X value of left edge of bounding box
	double GetXRight();			//!< Get X value of right edge of bounding box
	double GetYTop();			//!< Get Y value of top edge of bounding box
	double GetYBottom();			//!< Get Y value of bottom edge of bounding box
	coords GetTopLeft();			//!< Get struct containing coordinates of top left corner of bounding box
	coords GetTopRight();			//!< Get struct containing coordinates of top right corner of bounding box
	coords GetBottomLeft();			//!< Get struct containing coordinates of bottom left corner of bounding box
	coords GetBottomRight();		//!< Get struct containing coordinates of bottom right corner of bounding box
#if defined DEBUG
	static int Test();			//!< Run internal tests
#endif //DEBUG
private:
	coords _position;			//!< Struct that contains x and y positional coordinates
	coords _size;				//!< Struct that contains w and h of bounding box
	coords _center;				//!< Struct that contains x and y offset of center of bounding box
};

#endif //GEOMETRY_H
