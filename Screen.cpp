
#include "Screen.h"
#include <iostream>
#ifdef ASSERT
#include <assert.h>
#endif

using namespace std;

void Screen::drawPixel(int x,int y,Uint32 colour){
	if(x<0)
		return;
	if(y<0)
		return;
	if(x>=m_screenWidth)
		return;
	if(y>=m_screenHeight)
		return;

	//cout<<"drawPixel "<<x<<" "<<y<<endl;
	#ifdef ASSERT
	assert(x>=0);
	if(y<0)
		cout<<"y="<<y<<endl;
	assert(y>=0);
	assert(x<m_screenWidth);
	if(y>=m_screenHeight)
		cout<<"y="<<y<<endl;
	assert(y<m_screenHeight);
	#endif

	Uint32 *pixmem32 = (Uint32*) m_surface->pixels  + y*m_screenWidth + x;
	*pixmem32 = colour;
}

void Screen::drawLine(int x1,int y1,int x2,int y2,Uint32 colour){
	//cout<<"drawLine "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
	double slope=(y2-y1+0.0)/(x2-x1);

	if(x1>x2){
		drawLine(x2,y2,x1,y1,colour);
		return;
	}else if(x1==x2 && y1>y2){
		drawLine(x2,y2,x1,y1,colour);
		return;
	}

	if(x1==x2){
		for(int y=y1;y!=y2;y++){
			drawPixel(x1,y,colour);
		}
		return;
	}

	for(int x=x1;x!=x2;x++){
		int diffX=(x-x1);
		int diffY=slope*diffX;
		drawPixel(x1+diffX,y1+diffY,colour);
	}
}

void Screen::constructor(){
	m_screenWidth=640;
	m_screenHeight=480;
	SDL_Init( SDL_INIT_EVERYTHING );
	m_surface = SDL_SetVideoMode( m_screenWidth, m_screenHeight, 32, SDL_SWSURFACE );

}

void Screen::destructor(){
	SDL_Quit();
}

void Screen::clear(){
	Uint32 colour;  
	colour = SDL_MapRGB( m_surface->format, 255, 255, 255 );

	for(int x=0;x<m_screenWidth;x++){
		for(int y=0;y<m_screenHeight;y++){
			drawPixel(x,y,colour);
		}
	}
}

void Screen::display(){
	SDL_Flip(m_surface );
}

SDL_PixelFormat*Screen::getFormat(){
	return m_surface->format;
}

SDL_Surface*Screen::getSurface(){
	return m_surface;
}
