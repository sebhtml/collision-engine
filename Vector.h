/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#ifndef _Vector_H
#define _Vector_H

class Vector{
public:
	int m_x;
	int m_y;
	int m_z;

	Vector();
	Vector(int x,int y,int z);
	void constructor(int x,int y,int z);
	void addVector(Vector*vector);
	void computeProjectionOn(Vector*vector,Vector*result);
	void print();
};

#endif
