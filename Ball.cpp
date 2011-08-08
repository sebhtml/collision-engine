
#include "Ball.h"
#include <iostream>
#include <math.h>
using namespace std;


void Ball::update(){
	if(m_lastCollision>0)
		m_lastCollision--;
	double angle=toRadians(m_angle);

	m_preciseX+=m_speed*cos(angle)*PRECISION;
	m_preciseY+=m_speed*sin(angle)*PRECISION;
	m_x=m_preciseX/PRECISION;
	m_y=m_preciseY/PRECISION;
}

void Ball::display(Screen*screen){

	int lastX=m_x+m_radius;
	int lastY=m_y;

	for(int angle=0;angle<360;angle+=12){
		double radians=toRadians(angle);
		int newX=lastX;
		int newY=lastY;
		rotatePoint(m_x,m_y,m_x+m_radius,m_y,radians,&newX,&newY);
		screen->drawLine(lastX,lastY,newX,newY,colour);
		lastX=newX;
		lastY=newY;
	}
}


Ball::Ball(int x,int y,int r,int speed,int angle){
	m_x=x;
	m_y=y;
	m_radius=r;
	m_speed=speed;
	m_angle=angle;
	PRECISION=10000;
	m_preciseX=m_x*PRECISION;
	m_preciseY=m_y*PRECISION;
	m_lastCollision=10;
}

void Ball::processCollision(Object*object){
	if(m_lastCollision>0 && m_lastCollisionObject==object->getObjectIdentifier())
		return;
	int x=0;
	int y=0;
	if(object->detectCollisionWithCircle(m_x,m_y,m_radius,&x,&y)){
		//cout<<"Circle "<<m_x<<" "<<m_y<<" Collision "<<x<<" "<<y<<endl;
		int dx=x-m_x;
		int dy=y-m_y;

		if(dx==0){
			m_angle+=90;
		}else if(dy==0){
			m_angle+=90;
		}else{
			double angleInRadians=atan(dx/(dy+0.0));
			int degrees=toDegrees(angleInRadians);
			m_angle+=degrees;
		}
		m_angle%=360;
		m_lastCollision=10;
		m_lastCollisionObject=object->getObjectIdentifier();
	}
}

bool Ball::detectCollisionWithCircle(int x,int y, int r,int*xOut,int*yOut){
	return false;
}
