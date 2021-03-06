/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#include "OctreeAllocator.h"
#include <stdlib.h>
#include "OctreeNode.h"

OctreeAllocator::OctreeAllocator(){
	m_memory=NULL;
	m_freeNode=NULL;
}

/**
 * allocate 8 objects
 */
OctreeNode*OctreeAllocator::allocate(){
	int n=8;
	if(m_freeNode!=NULL){
		OctreeNode*value=m_freeNode;
		m_freeNode=m_freeNode->m_children;
		return value;
	}

	if(m_memory==NULL || m_memory->m_head==m_memory->m_size){
		int nodesPerBlock=128*n;
		MemoryBlock*block=(MemoryBlock*)malloc(sizeof(MemoryBlock));
		block->m_memory=(OctreeNode*)malloc(nodesPerBlock*sizeof(OctreeNode));
		block->m_head=0;
		block->m_size=nodesPerBlock;
		block->m_next=m_memory;
		m_memory=block;
	}

	OctreeNode*value=m_memory->m_memory+m_memory->m_head;
	m_memory->m_head+=n;
	return value;
}

void OctreeAllocator::free(OctreeNode*node){
	node->m_children=m_freeNode;
	m_freeNode=node;
}
