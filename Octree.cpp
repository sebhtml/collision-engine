
#include "Octree.h"

void Octree::constructor(int x,int y,int z,int max){
	m_xLength=x;
	m_yLength=y;
	m_zLength=z;
	m_max=max;
	m_root.constructor(0,x-1,0,y-1,0,z-1);
}

void Octree::remove(int x,int y,int z,int r,uint64_t object){
	vector<Vector> points;
	getPoints(x,y,z,r,&points);
	for(int i=0;i<(int)points.size();i++)
		m_root.remove(&(points[i]),object,&m_allocator);
}

void Octree::add(int x,int y,int z,int r,uint64_t object){
	vector<Vector> points;
	getPoints(x,y,z,r,&points);
	for(int i=0;i<(int)points.size();i++)
		m_root.add(&(points[i]),object,&m_allocator);
}

void Octree::getList(int x,int y,int z,int r,set<uint64_t>*output){
	vector<Vector> points;
	getPoints(x,y,z,r,&points);
	for(int i=0;i<(int)points.size();i++)
		m_root.getList(&(points[i]),output);
}

void Octree::getPoints(int x,int y,int z,int r,vector<Vector>*output){
	Vector p;
	p.constructor(x-r,y-r,z-r);
	output->push_back(p);
	p.constructor(x-r,y-r,z+r);
	output->push_back(p);
	p.constructor(x-r,y+r,z-r);
	output->push_back(p);
	p.constructor(x-r,y+r,z+r);
	output->push_back(p);
	p.constructor(x+r,y-r,z-r);
	output->push_back(p);
	p.constructor(x+r,y-r,z+r);
	output->push_back(p);
	p.constructor(x+r,y+r,z-r);
	output->push_back(p);
	p.constructor(x+r,y+r,z+r);
	output->push_back(p);
}
