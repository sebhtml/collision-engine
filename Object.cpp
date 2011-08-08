
#include "Object.h"
#include <math.h>
#include <iostream>
using namespace std;

void Object::rotatePoint(int x0,int y0,int x,int y,double theta,int*x2,int*y2){
	(*x2) = x0+(x-x0)*cos(theta)+(y-y0)*sin(theta);
	(*y2) = y0-(x-x0)*sin(theta)+(y-y0)*cos(theta);
}

double Object::toRadians(int angle){
	double PI=3.14159265;
	double angleInRadians=angle*PI/180;
	return angleInRadians;
}

void Object::setObjectIdentifier(uint64_t a){
	m_objectIdentifier=a;
}

uint64_t Object::getObjectIdentifier(){
	return m_objectIdentifier;
}

int sgn(int a){
	if(a>0)
		return 1;
	else
		return -1;
}

int abs(int a){
	if(a<0)
		return -a;
	return a;
}

bool Object::detectCollisionBetweenCircleAndLine(int x,int y,int r,int x1ori,int y1ori,int x2ori,int y2ori,int*xOut,int*yOut){
	/* vertical line */
	if(x1ori==x2ori){
		if((x-r)<= x1ori && x1ori <= (x+r)){
			(*xOut)=x1ori;
			(*yOut)=y;
			return true;
		}else{
			return false;
		}
	}

	/* horizontal line */
	if(y1ori==y2ori){
		if((y-r)<=y1ori && y1ori <= (y+r)){
			(*xOut)=x;
			(*yOut)=y1ori;
			return true;
		}else{
			return false;
		}
	}

	int x1=x1ori-x;
	int y1=y1ori-y;
	int x2=x2ori-x;
	int y2=y2ori-y;

	int dx=x2-x1;
	int dy=y2-y1;
	int drdr=dx*dx+dy*dy;
	//double dr=sqrt(drdr+0.0);
	int D=x1*y2-x2*y1;
	int discriminant=r*r+drdr-D*D;

	/* 0 = tangent, <0 = no intersection */
	if(discriminant<=0)
		return false;

	double xPlus= (D*dy+sgn(dy)*dx*sqrt(discriminant+0.0))/drdr;
	double xMinus=(D*dy-sgn(dy)*dx*sqrt(discriminant+0.0))/drdr;
	double yPlus= (-D*dx+abs(dy)*sqrt(discriminant+0.0))/drdr;	
	double yMinus=(-D*dx-abs(dy)*sqrt(discriminant+0.0))/drdr;	

	/* compute average and move according to the center of the circle */
	(*xOut)=(xPlus+xMinus)/2+x;
	(*yOut)=(yPlus+yMinus)/2+y;

	/* we want the collision to be real */
	return (x1ori<=(*xOut) && (*xOut)<=x2ori);
}
