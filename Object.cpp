
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

int Object::toDegrees(double radians){
	double PI=3.14159265;
	return radians*180/PI;
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

/**
 *
 * \see http://paulbourke.net/geometry/sphereline/
 */
bool Object::detectCollisionBetweenCircleAndLine(int x,int y,int r,int x1ori,int y1ori,int x2ori,int y2ori,int*xOut,int*yOut){
	int seg_v_x=x2ori-x1ori;
	int seg_v_y=y2ori-y1ori;
	int pt_v_x=x-x1ori;
	int pt_v_y=y-y1ori;
	
	double seg_v_length=sqrt(seg_v_x*seg_v_x+seg_v_y*seg_v_y+0.0);
	double proj_v_length=(pt_v_x*seg_v_x+pt_v_y*seg_v_y)/seg_v_length;

	double proj_v_x=seg_v_x*proj_v_length/seg_v_length;
	double proj_v_y=seg_v_y*proj_v_length/seg_v_length;

	double closest_x=proj_v_x+x1ori;
	double closest_y=proj_v_y+y1ori;

	double dist_v_x=x-closest_x;
	double dist_v_y=y-closest_y;

	double distance=sqrt(dist_v_x*dist_v_x+dist_v_y*dist_v_y+0.0);
	
	if(distance>r)
		return false;

	(*xOut)=closest_x;
	(*yOut)=closest_y;

	if(x1ori<= closest_x && closest_x <=x2ori){
		if(y1ori <= closest_y && closest_y <= y2ori)
			return true;
		if(y2ori <= closest_y && closest_y <= y1ori)
			return true;
	}
	if(x2ori<= closest_x && closest_x <=x1ori){
		if(y1ori <= closest_y && closest_y <= y2ori)
			return true;
		if(y2ori <= closest_y && closest_y <= y1ori)
			return true;
	}


	return false;
}
