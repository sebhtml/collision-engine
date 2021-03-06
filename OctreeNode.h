/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#ifndef _OctreeNode_H
#define _OctreeNode_H

#include "Vector.h"
#include "OctreeAllocator.h"
#include <set>
#include <stdint.h>
#include <vector>
using namespace std;

class OctreeAllocator;

class OctreeNode{
	bool m_debug;
	int m_maxPerNode;
	int m_depth;

	uint64_t m_objects[8];
	Vector m_objectPoints[8];

	int m_numberOfObjects;
	int m_xStart;
	int m_xEnd;
	int m_yStart;
	int m_yEnd;
	int m_zStart;
	int m_zEnd;


public:
	OctreeNode*m_children;

	void constructor(int xStart,int xEnd,int yStart,int yEnd,int zStart,int zEnd,int maxPerNode,int depth);
	void remove(Vector*point,uint64_t object,OctreeAllocator*allocator);
	void add(Vector*point,uint64_t object,OctreeAllocator*allocator);
	void getList(Vector*point,set<uint64_t>*output);
	bool hasPoint(Vector*point);
	int getObjects();
	bool hasChildren();
	void print();
};

#endif
