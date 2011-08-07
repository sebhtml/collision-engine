
#ifndef _Ball_H
#define _Ball_H

#include "Object.h"

class Ball: public Object{
	int m_angle;
	int m_speed;
	int m_x;
	int m_y;
	int m_radius;
public:
	Ball(int x,int y,int r,int speed,int angle);
	void update();
	void display(Screen*screen);
};

#endif
