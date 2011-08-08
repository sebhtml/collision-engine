
#include "Ball.h"
#include <iostream>
#include <math.h>
using namespace std;

void Ball::update(){
	double angleInRadians=toRadians(m_angle);
	int deltaX=m_speed*cos(angleInRadians);
	int deltaY=m_speed*sin(angleInRadians);
	m_x+=deltaX;
	m_y+=deltaY;
}

void Ball::display(Screen*screen){
	int lastX=m_x+m_radius;
	int lastY=m_y;

	Uint32 colour;  
	colour = SDL_MapRGB( screen->getFormat(), 40,40,50);
	for(int angle=0;angle<360;angle++){
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
}

void Ball::processCollision(Object*object){
	int x=0;
	int y=0;
	if(object->detectCollisionWithCircle(m_x,m_y,m_radius,&x,&y)){
		m_angle+=180;
		if(m_angle>=360)
			m_angle=m_angle%360;
	}
}

bool Ball::detectCollisionWithCircle(int x,int y, int r,int*xOut,int*yOut){
	return false;
}
