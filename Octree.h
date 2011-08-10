
#ifndef _Octree_H
#define _Octree_H

#include <stdint.h>
#include "OctreeNode.h"
#include "Vector.h"
#include <vector>
#include <set>
using namespace std;


class Octree{
	OctreeAllocator m_allocator;
	int m_max;
	OctreeNode m_root;
	int m_xLength;
	int m_yLength;
	int m_zLength;

	void getPoints(int x,int y,int z,int r,vector<Vector>*output);
public:
	void remove(int x,int y,int z,int r,uint64_t object);
	void add(int x,int y,int z,int r,uint64_t object);
	void getList(int x,int y,int z,int r,set<uint64_t>*output);
	void constructor(int x,int y,int z,int max);
};

#endif
