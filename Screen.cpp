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

typedef struct {
	int X;
	int Y;
	int Z;
	double U;
	double V;
}Vertex;


void CreateSphere (double R, double H, double K, double Z,Vertex*vertices,
	int space) {
	const double PI = 3.1415926535897;
	int n;
	double a;
	double b;
	n = 0;
    
	for( b = 0; b <= 90 - space; b+=space){
		for( a = 0; a <= 360 - space; a+=space){
			vertices[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
			vertices[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
			vertices[n].Z = R * cos((b) / 180 * PI) - Z;
			vertices[n].V = (2 * b) / 360;
			vertices[n].U = (a) / 360;
			n++;
            
			vertices[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
			vertices[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
			vertices[n].Z = R * cos((b + space) / 180 * PI) - Z;
			vertices[n].V = (2 * (b + space)) / 360;
			vertices[n].U = (a) / 360;
			n++;
            
			vertices[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
			vertices[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
			vertices[n].Z = R * cos((b) / 180 * PI) - Z;
			vertices[n].V = (2 * b) / 360;
			vertices[n].U = (a + space) / 360;
			n++;
            
			vertices[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) / 180 * PI) - H;
			vertices[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) / 180 * PI) + K;
			vertices[n].Z = R * cos((b + space) / 180 * PI) - Z;
			vertices[n].V = (2 * (b + space)) / 360;
			vertices[n].U = (a + space) / 360;
			n++;
		}
	}
}

void DisplaySphere (Vertex*vertices,int vertexCount){
	int b;
	glBegin (GL_TRIANGLES);
	glColor3f(255,0,0);
	for ( b = 0; b <= vertexCount; b++){
		glVertex3f (vertices[b].X, vertices[b].Y, -vertices[b].Z);
	}

	for ( b = 0; b <= vertexCount; b++){
		glVertex3f (vertices[b].X, vertices[b].Y, vertices[b].Z);
	}
    
	glEnd();
}

void Screen::drawSphere(int x,int y,int z,int r){
	x/=m_precision;
	y/=m_precision;
	z/=m_precision;

	glLoadIdentity();
	gluLookAt(m_eyeX,m_eyeY,m_eyeZ, 0, 400, -100, 1, 2, 0); //for example

	glTranslatef(x,y,z);
	glCallList(m_sphereDisplayList);
}

void Screen::constructor(int width,int height,int precision,int radius){
	m_eyeX=0;
	m_eyeY=300;
	m_eyeZ=300;
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

	int space=10;
	int vertexCount=((90 / space) * (360 / space) * 4);

	Vertex*vertices=(Vertex*)malloc(vertexCount*sizeof(Vertex));

	CreateSphere (radius,0,0,0,vertices,space);

	m_sphereDisplayList=glGenLists(2);
	m_backgroundDisplayList=m_sphereDisplayList+1;
	glNewList(m_sphereDisplayList,GL_COMPILE);
	DisplaySphere(vertices,vertexCount);
	glEndList();

	free(vertices);
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
}

void Screen::display(){
	// Swap the buffers
	SDL_GL_SwapBuffers();
}

void Screen::increaseEyeX(){
	m_eyeX++;
}

void Screen::decreaseEyeX(){
	m_eyeX--;
}

void Screen::increaseEyeY(){
	m_eyeY++;
}

void Screen::decreaseEyeY(){
	m_eyeY--;
}
