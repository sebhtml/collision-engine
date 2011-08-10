/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#ifndef _Octree_H
#define _Octree_H

#include <stdint.h>
#include "OctreeNode.h"
#include "Vector.h"
#include <vector>
#include <set>
using namespace std;

class Octree{
	bool m_debug;
	OctreeAllocator m_allocator;
	OctreeNode m_root;
	int m_xLength;
	int m_yLength;
	int m_zLength;

	void getPoints(Vector*center,int r,vector<Vector>*output);

public:
	void remove(Vector*center,int r,uint64_t object);
	void add(Vector*center,int r,uint64_t object);
	void getList(Vector*center,int r,set<uint64_t>*output);
	void constructor(int x,int y,int z);
};

#endif
