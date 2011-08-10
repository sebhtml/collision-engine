
#ifndef _OctreeAllocator_H
#define _OctreeAllocator_H

#include "OctreeNode.h"

class OctreeNode;

class MemoryBlock{
public:
	OctreeNode*m_memory;
	int m_head;
	int m_size;
	MemoryBlock*m_next;
};

class OctreeAllocator{
	MemoryBlock*m_memory;
	OctreeNode*m_freeNode;
public:
	OctreeAllocator();
	OctreeNode*allocate();
	void free(OctreeNode*node);
};

#endif
