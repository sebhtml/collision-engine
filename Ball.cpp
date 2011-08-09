
#include "Ball.h"
#include <iostream>
#include <math.h>
using namespace std;


void Ball::update(){
	m_center.addVector(&m_direction);
}

void Ball::display(Screen*screen){
	int lastX=m_center.m_x+m_radius;
	int lastY=m_center.m_y;

	for(int angle=0;angle<360;angle+=12){
		double radians=toRadians(angle);
		int newX=0;
		int newY=0;
		rotatePoint(m_center.m_x,m_center.m_y,m_center.m_x+m_radius,m_center.m_y,radians,&newX,&newY);
		
		screen->drawLine(lastX,lastY,newX,newY,m_colour);
		lastX=newX;
		lastY=newY;
	}
}


Ball::Ball(Vector*center,int radius,Vector*direction){
	m_center.m_x=center->m_x;
	m_center.m_y=center->m_y;
	m_center.m_z=center->m_z;
	m_direction.m_x=direction->m_x;
	m_direction.m_y=direction->m_y;
	m_direction.m_z=direction->m_z;
	m_radius=radius;
	m_colour=0;
}

void Ball::processCollision(Object*object){
	Vector collisionPoint;
	if(object->detectCollisionWithSphere(&m_center,m_radius,&collisionPoint)){
		Vector collisionVector;
		collisionVector.m_x=collisionPoint.m_x-m_center.m_x;
		collisionVector.m_y=collisionPoint.m_y-m_center.m_y;
		collisionVector.m_z=collisionPoint.m_z-m_center.m_z;

		cout<<"CollisionVector "<<collisionVector.m_x<<" "<<collisionVector.m_y<<endl;
		Vector projection;

		m_direction.computeProjectionOn(&collisionVector,&projection);
		cout<<"DirectionVector "<<m_direction.m_x<<" "<<m_direction.m_y<<endl;
		cout<<"Projection of direction on collisionVector "<<projection.m_x<<" "<<projection.m_y<<endl;

		cout<<"Speed before "<<getSpeed()<<endl;
		m_direction.m_x-=2*projection.m_x;
		m_direction.m_y-=2*projection.m_y;
		m_direction.m_z-=2*projection.m_z;

		cout<<"Speed after "<<getSpeed()<<endl;
	}
}

bool Ball::detectCollisionWithSphere(Vector*center,int radius,Vector*collision){
	float expected=(radius+m_radius);
	float dx=m_center.m_x-center->m_x;
	float dy=m_center.m_y-center->m_y;
	float dz=m_center.m_z-center->m_z;

/*
make things faster
	float squareExpected=expected*expected;
	float constant=0.866025403784439;
	if(dx>=squareExpected*constant||dy>=squareExpected*constant||dz>=squareExpected*constant)
		return false;
*/
	float observed=sqrt(dx*dx+dy*dy+dz*dz+0.0);
	if(observed>expected)
		return false;
	collision->m_x=(m_center.m_x+center->m_x)/2;
	collision->m_y=(m_center.m_y+center->m_y)/2;
	collision->m_z=(m_center.m_z+center->m_z)/2;

	cout<<endl;
	cout<<"Collision"<<endl;
	cout<<"Distance: "<<observed<<" threshold: "<<expected<<endl;
	cout<<"Center1 "<<m_center.m_x<<" "<<m_center.m_y<<endl;
	cout<<"Center2 "<<center->m_x<<" "<<center->m_y<<endl;

	cout<<"CollisionPoint "<<collision->m_x<<" "<<collision->m_y<<endl;
	return true;
}

int Ball::getSpeed(){
	return sqrt(m_direction.m_x*m_direction.m_x+m_direction.m_y*m_direction.m_y+m_direction.m_z*m_direction.m_z+0.0);
}
