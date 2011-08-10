/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#ifndef _Ball_H
#define _Ball_H

#include "Object.h"
#include "Vector.h"

class Ball: public Object{
	Vector m_direction;
	Uint32 m_colour;  
public:
	Ball(Vector*center,int radius,Vector*direction);
	void update(Octree*octree);
	void display(Screen*screen);
	void processCollision(Object*object);
	bool detectCollisionWithSphere(Vector*center, int r,Vector*collision);
	int getSpeed();
	bool isMoving();
};

#endif
