
#ifndef _Object_H
#define _Object_H

#include "Screen.h"

class Object{

public:
	virtual void update() = 0;
	virtual void display(Screen*screen) = 0;
	void rotatePoint(int x0,int y0,int x,int y,double theta,int*x2,int*y2);
	double toRadians(int angle);
};

#endif
