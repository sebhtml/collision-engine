/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#include <math.h>
#include <SDL/SDL.h>
#include "Screen.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#ifdef ASSERT
#include <assert.h>
#endif

using namespace std;

/* some of the OpenGL is from the Internet */

typedef struct 
{
    
int X;
    
int Y;
    
int Z;
    

    
double U;
    
double V;
}VERTICES;

const double PI = 3.1415926535897;

#define space  10

#define VertexCount ((90 / space) * (360 / space) * 4)

VERTICES VERTEX[VertexCount];

void CreateSphere (double R, double H, double K, double Z) {
    
int n;
    
double a;
    
double b;
    

    
n = 0;
    

    
for( b = 0; b <= 90 - space; b+=space){
        
    for( a = 0; a <= 360 - space; a+=space){
            

            
VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
            
VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
            
VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
            
VERTEX[n].V = (2 * b) / 360;
            
VERTEX[n].U = (a) / 360;
            
n++;
            

            
VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI
            
) - H;
            
VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI
            
) + K;
            
VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
            
VERTEX[n].V = (2 * (b + space)) / 360;
            
VERTEX[n].U = (a) / 360;
            
n++;
            

            
VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI
            
) - H;
            
VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI
            
) + K;
            
VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
            
VERTEX[n].V = (2 * b) / 360;
            
VERTEX[n].U = (a + space) / 360;
            
n++;
            

            
VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) / 
            
180 * PI) - H;
            
VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) / 
            
180 * PI) + K;
            
VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
            
VERTEX[n].V = (2 * (b + space)) / 360;
            
VERTEX[n].U = (a + space) / 360;
            
n++;
            

            
    }
    
}
}

void DisplaySphere (){

int b;
    
   
glBegin (GL_TRIANGLES);
    glColor3f(255,0,0);
for ( b = 0; b <= VertexCount; b++){
        
//glTexCoord2f (VERTEX[b].U, VERTEX[b].V);
        
glVertex3f (VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);

//cout<<" "<<VERTEX[b].X<<" "<<VERTEX[b].Y<<" "<<VERTEX[b].Z<<endl;
    
}

for ( b = 0; b <= VertexCount; b++){
        
//glTexCoord2f (VERTEX[b].U, -VERTEX[b].V);
        
glVertex3f (VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);
    
}
    
glEnd();

}

void Screen::drawSphere(int x,int y,int z,int r){
	x/=m_precision;
	y/=m_precision;
	z/=m_precision;

	glLoadIdentity();
	//gluLookAt(m_screenWidth/2,m_screenHeight/2,100,		m_screenWidth*3/4,0,0,		1,1,1);
	gluLookAt(0, 300, 300, 0, 400, -100, 1, 2, 0); //for example

	//gluLookAt(15,100,10,	200,0,0,	1,0,0);

	glTranslatef(x,y,z);
	glCallList(m_sphereDisplayList);
}

void Screen::constructor(int width,int height,int precision){
	m_screenWidth=width;
	m_screenHeight=height;
	m_precision=precision;

	SDL_Init(SDL_INIT_EVERYTHING);
	if(SDL_SetVideoMode(m_screenWidth, m_screenHeight, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)==NULL)
		cout<<"Error"<<endl;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, width, 0, height, -1000, +1000);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//glEnable(GL_CULL_FACE);
	//glEnable(GL_TEXTURE_2D);
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_LIGHTING);
        //glEnable(GL_LIGHT0);
        //glEnable(GL_NORMALIZE);
	//glEnable(GL_COLOR_MATERIAL);

	CreateSphere (10,0,0,0);

	m_sphereDisplayList=glGenLists(2);
	m_backgroundDisplayList=m_sphereDisplayList+1;
	glNewList(m_sphereDisplayList,GL_COMPILE);
	DisplaySphere();
	glEndList();
	
	//gluPerspective();
}

void Screen::startBackground(){
	glNewList(m_backgroundDisplayList,GL_COMPILE);
}

void Screen::endBackground(){
	glEndList();
}

void Screen::displayBackground(){
	glCallList(m_backgroundDisplayList);
}

void Screen::destructor(){
}

void Screen::clear(){
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(1,1,1,0,0,0,0,1,0);
}

void Screen::display(){
	SDL_GL_SwapBuffers(); // Swap the buffers
}


