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
	int m_eyeX;
	int m_eyeY;
	int m_eyeZ;
public:
	void constructor(int width,int height,int precision,int radius);
	void destructor();
	void display();
	void clear();
	void drawSphere(int x,int y,int z,int r);
	void startBackground();
	void endBackground();
	void displayBackground();
	void increaseEyeX();
	void decreaseEyeX();
	void increaseEyeY();
	void decreaseEyeY();
};

#endif
