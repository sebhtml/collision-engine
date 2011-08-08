
#include "Wall.h"
#include <math.h>
#include <iostream>
using namespace std;

Wall::Wall(int centerX,int centerY,int width,int height,int angle,int red,int green,int blue){
	m_x=centerX;
	m_y=centerY;
	m_width=width;
	m_height=height;
	m_angle=angle;
	m_red=red;
	m_green=green;
	m_blue=blue;
	m_rotate=true;
}

void Wall::update(){
/*
	if(m_rotate){
		m_angle++;
		m_rotate=false;
	}else{
		m_angle--;
		m_rotate=true;
	}
	m_angle%=360;
*/
}

void Wall::display(Screen*screen){
	int left=m_x-m_width/2;
	int right=m_x+m_width/2;
	int top=m_y-m_height/2;
	int bottom=m_y+m_height/2;

	double angleInRadians=toRadians(m_angle);

	int x1=left;
	int y1=top;
	rotatePoint(m_x,m_y,x1,y1,angleInRadians,&x1,&y1);
	int x2=right;
	int y2=top;
	rotatePoint(m_x,m_y,x2,y2,angleInRadians,&x2,&y2);
	int x3=right;
	int y3=bottom;
	rotatePoint(m_x,m_y,x3,y3,angleInRadians,&x3,&y3);
	int x4=left;
	int y4=bottom;
	rotatePoint(m_x,m_y,x4,y4,angleInRadians,&x4,&y4);

	Uint32 colour;  
	colour = SDL_MapRGB( screen->getFormat(), m_red,m_green,m_blue);

	screen->drawLine(x1,y1,x2,y2,colour);
	screen->drawLine(x2,y2,x3,y3,colour);
	screen->drawLine(x3,y3,x4,y4,colour);
	screen->drawLine(x4,y4,x1,y1,colour);
}

void Wall::freeze(){
	m_rotate=false;
}

void Wall::processCollision(Object*object){
}

bool Wall::detectCollisionWithCircle(int x,int y, int r,int*xOut,int*yOut){
	int left=m_x-m_width/2;
	int right=m_x+m_width/2;
	int top=m_y-m_height/2;
	int bottom=m_y+m_height/2;

	double angleInRadians=toRadians(m_angle);

	int x1=left;
	int y1=top;
	rotatePoint(m_x,m_y,x1,y1,angleInRadians,&x1,&y1);
	int x2=right;
	int y2=top;
	rotatePoint(m_x,m_y,x2,y2,angleInRadians,&x2,&y2);
	int x3=right;
	int y3=bottom;
	rotatePoint(m_x,m_y,x3,y3,angleInRadians,&x3,&y3);
	int x4=left;
	int y4=bottom;
	rotatePoint(m_x,m_y,x4,y4,angleInRadians,&x4,&y4);

	if(detectCollisionBetweenCircleAndLine(x,y,r,x1,y1,x2,y2,xOut,yOut))
		return true;
	if(detectCollisionBetweenCircleAndLine(x,y,r,x2,y2,x3,y3,xOut,yOut))
		return true;
	if(detectCollisionBetweenCircleAndLine(x,y,r,x3,y3,x4,y4,xOut,yOut))
		return true;
	if(detectCollisionBetweenCircleAndLine(x,y,r,x4,y4,x1,y1,xOut,yOut))
		return true;
	
	return false;
}
