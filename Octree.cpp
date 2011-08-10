/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#include "Octree.h"
#include <iostream>
using namespace std;

void Octree::constructor(int x,int y,int z){
	m_xLength=x;
	m_yLength=y;
	m_zLength=z;
	int maxPerNode=4;
	m_root.constructor(0,x-1,0,y-1,0,z-1,maxPerNode,0);
	m_debug=false;
}

void Octree::remove(Vector*center,int r,uint64_t object){
	if(m_debug)
		cout<<"Octree: removing object "<<object<<" point "<<center->m_x<<" "<<center->m_y<<" "<<center->m_z<<" radius "<<r<<endl;
	vector<Vector> points;
	getPoints(center,r,&points);
	for(int i=0;i<(int)points.size();i++){
		m_root.remove(&(points[i]),object,&m_allocator);
	}
}

void Octree::add(Vector*center,int r,uint64_t object){
	if(m_debug){
		cout<<endl;
		cout<<"Octree: adding object "<<object<<" point "<<center->m_x<<" "<<center->m_y<<" "<<center->m_z<<" radius "<<r<<endl;
	}

	vector<Vector> points;
	getPoints(center,r,&points);
	for(int i=0;i<(int)points.size();i++){
		m_root.add(&(points[i]),object,&m_allocator);
	}
}

void Octree::getList(Vector*center,int r,set<uint64_t>*output){
	vector<Vector> points;
	getPoints(center,r,&points);
	for(int i=0;i<(int)points.size();i++){
		m_root.getList(&(points[i]),output);
	}
}

void Octree::getPoints(Vector*center,int r,vector<Vector>*output){
	Vector p;
	int x=center->m_x;
	int y=center->m_y;
	int z=center->m_z;
	p.constructor(x,y,z);
	output->push_back(p);
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
