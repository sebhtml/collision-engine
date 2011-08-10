
#include "Vector.h"
#include <iostream>
#include <stdint.h>
using namespace std;

void Vector::addVector(Vector*vector){
	m_x+=vector->m_x;
	m_y+=vector->m_y;
	m_z+=vector->m_z;
}

Vector::Vector(){
	m_x=0;
	m_y=0;
	m_z=0;
}

Vector::Vector(int x,int y,int z){
	m_x=x;
	m_y=y;
	m_z=z;
}

void Vector::computeProjectionOn(Vector*vector,Vector*result){
	int64_t dotProduct1=(int64_t)m_x*vector->m_x+m_y*vector->m_y+m_z*vector->m_z;
	int64_t dotProduct2=(int64_t)vector->m_x*vector->m_x+vector->m_y*vector->m_y+vector->m_z*vector->m_z;
	float factor=dotProduct1/(dotProduct2+0.0);
	result->m_x=vector->m_x*factor;
	result->m_y=vector->m_y*factor;
	result->m_z=vector->m_z*factor;
}
