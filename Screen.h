
#ifndef _Screen_H
#define _Screen_H

#include <SDL/SDL.h>

class Screen{
	int m_screenWidth;
	int m_screenHeight;
	int m_precision;
	SDL_Surface*m_surface;
public:
	void constructor(int width,int height,int precision);
	void destructor();
	void display();
	void clear();
	void drawSphere(int x,int y,int z,int r);
};

#endif
