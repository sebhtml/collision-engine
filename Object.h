/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#ifndef _Object_H
#define _Object_H

#include "Screen.h"
#include <stdint.h>
#include "Vector.h"
#include "Octree.h"

class Object{
	uint64_t m_objectIdentifier;
protected:
	Vector m_center;
	int m_radius;

public:
	virtual bool isMoving()=0;
	virtual void update(Octree*octree) = 0;
	virtual void display(Screen*screen) = 0;
	virtual void processCollision(Object*object) = 0;
	virtual bool detectCollisionWithSphere(Vector*center,int radius,Vector*collision) =0;

	void rotatePoint(int x0,int y0,int x,int y,double theta,int*x2,int*y2);
	double toRadians(int angle);
	int toDegrees(double radians);
	void setObjectIdentifier(uint64_t a);
	uint64_t getObjectIdentifier();

	bool detectCollisionBetweenCircleAndLine(int x,int y,int r,int x4,int y4,int x1,int y1,int*xOut,int*yOut);
	void getGeometry(Vector*center,int*radius);
};

#endif
