/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#ifndef _Wall_H
#define _Wall_H

#include "Object.h"

class Wall: public Object{
	int m_angle;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_red;
	int m_green;
	int m_blue;
	bool m_rotate;
public:
	void update();
	void freeze();
	void display(Screen*screen);
	Wall(int centerX,int centerY,int width,int height,int angle,int red,int green,int blue);
	void processCollision(Object*object);
	bool detectCollisionWithCircle(int x,int y, int r,int*xOut,int*yOut);
};

#endif
