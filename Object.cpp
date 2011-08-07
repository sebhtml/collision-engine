
#include "Object.h"
#include <math.h>

void Object::rotatePoint(int x0,int y0,int x,int y,double theta,int*x2,int*y2){
	(*x2) = x0+(x-x0)*cos(theta)+(y-y0)*sin(theta);
	(*y2) = y0-(x-x0)*sin(theta)+(y-y0)*cos(theta);
}

double Object::toRadians(int angle){
	double PI=3.14159265;
	double angleInRadians=angle*PI/180;
	return angleInRadians;
}
