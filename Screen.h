/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#ifndef _Screen_H
#define _Screen_H

#include <SDL/SDL.h>
#include <GL/gl.h>

class Screen{
	GLuint m_sphereDisplayList;
	GLuint m_backgroundDisplayList;
	int m_screenWidth;
	int m_screenHeight;
	int m_precision;
public:
	void constructor(int width,int height,int precision);
	void destructor();
	void display();
	void clear();
	void drawSphere(int x,int y,int z,int r);
	void startBackground();
	void endBackground();
	void displayBackground();
};

#endif
