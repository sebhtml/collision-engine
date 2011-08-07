
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
}

void Wall::update(){
	m_angle++;
	if(m_angle==360)
		m_angle=0;
}

void rotatePoint(int x0,int y0,int x,int y,double theta,int*x2,int*y2){
	(*x2) = x0+(x-x0)*cos(theta)+(y-y0)*sin(theta);
	(*y2) = y0-(x-x0)*sin(theta)+(y-y0)*cos(theta);
}

void Wall::display(Screen*screen){
	double PI=3.14159265;

	int left=m_x-m_width/2;
	int right=m_x+m_width/2;
	int top=m_y-m_height/2;
	int bottom=m_y+m_height/2;

	double angleInRadians=m_angle*PI/180;

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
