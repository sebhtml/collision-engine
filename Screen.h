
#ifndef _Screen_H
#define _Screen_H

#include <SDL/SDL.h>

class Screen{
	int m_screenWidth;
	int m_screenHeight;
	int m_precision;
	SDL_Surface*m_surface;
public:
	void drawPixel(int x,int y,Uint32 colour);
	void drawLine(int x1,int y1,int x2,int y2,Uint32 colour);
	void constructor(int width,int height,int precision);
	void destructor();
	void display();
	SDL_PixelFormat*getFormat();
	void clear();
	SDL_Surface*getSurface();
};

#endif
