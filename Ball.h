
#ifndef _Ball_H
#define _Ball_H

#include "Object.h"

class Ball: public Object{
	int PRECISION;
	int m_speed;
	int m_angle;
	int m_radius;
	int m_preciseX;
	int m_preciseY;
	Uint32 colour;  
public:
	Ball(int x,int y,int r,int speed,int angle);
	void update();
	void display(Screen*screen);
	void processCollision(Object*object);
	bool detectCollisionWithCircle(int x,int y, int r,int*xOut,int*yOut);
};

#endif
