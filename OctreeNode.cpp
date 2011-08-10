/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#include "OctreeNode.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>

void OctreeNode::constructor(int xStart,int xEnd,int yStart,int yEnd,int zStart,int zEnd,int maxPerNode,int depth){
	m_debug=false;
	m_depth=depth;
	m_maxPerNode=maxPerNode;
	m_children=NULL;
	m_numberOfObjects=0;
	m_xStart=xStart;
	m_xEnd=xEnd;
	m_yStart=yStart;
	m_yEnd=yEnd;
	m_zStart=zStart;
	m_zEnd=zEnd;
	if(m_debug){
		cout<<"OctreeNode builded node"<<endl;
		print();
	}
}

void OctreeNode::remove(Vector*point,uint64_t object,OctreeAllocator*allocator){
	if(m_debug)
		cout<<"Entering OctreeNode::remove"<<endl;
	if(!hasPoint(point))
		return;

	if(m_children==NULL){
		/* remove from object list */
		for(int i=0;i<m_numberOfObjects;i++){
			if(m_objects[i]==object){
				for(int j=i+1;j<m_numberOfObjects;j++){
					m_objects[j-1]=m_objects[j];
					m_objectPoints[j-1]=m_objectPoints[j];
				}
				m_numberOfObjects--;
				if(m_debug)
					cout<<"OctreeNode: removed "<<object<<" ("<<m_numberOfObjects+1<<" -> "<<m_numberOfObjects<<") point: "<<point->m_x<<" "<<point->m_y<<" "<<point->m_z<<" boundaries: x "<<m_xStart<<" "<<m_xEnd<<" y "<<m_yStart<<" "<<m_yEnd<<" z "<<m_zStart<<" "<<m_zEnd<<endl;
				break;
			}
		}
	}else{
		#ifdef ASSERT
		assert(m_numberOfObjects == 0);
		#endif

		int total=0;
		bool childrenHasChildren=false;
		/* ask children */
		for(int i=0;i<8;i++){
			m_children[i].remove(point,object,allocator);
			total+=m_children[i].getObjects();
			if(m_children[i].hasChildren())
				childrenHasChildren=true;
		}
	
		/* if all the children are empty, free them */
		/* next time we add something, it will be added in the object list */
		if(total == 0 && !childrenHasChildren){
			if(m_debug)
				cout<<"OctreeNode: no objects in children, freeing children..."<<endl;
			allocator->free(m_children);
			m_children=NULL;
		}
	}
}

void OctreeNode::add(Vector*point,uint64_t object,OctreeAllocator*allocator){
	if(m_debug)
		cout<<"OctreeNode (depth "<<m_depth<<"): adding "<<object<<" point: "<<point->m_x<<" "<<point->m_y<<" "<<point->m_z<<" boundaries: x "<<m_xStart<<" "<<m_xEnd<<" y "<<m_yStart<<" "<<m_yEnd<<" z "<<m_zStart<<" "<<m_zEnd<<endl;
	if(!hasPoint(point)){
		if(m_debug)
			cout<<"not in boundaries"<<endl;
		return;
	}

	if(m_debug)
		cout<<"within boundaries"<<endl;

	if(m_children==NULL){
		if(m_debug)
			cout<<"OctreeNode: no children, checking object list"<<endl;
		/* check if the object is present already */
		for(int i=0;i<m_numberOfObjects;i++){
			if(m_objects[i]==object){
				if(m_debug)
					cout<<"Object "<<object<<" is already there."<<endl;
				return;
			}
		}
		/* the object is not present */
		if(m_numberOfObjects<m_maxPerNode){
			/* we can add it */
			m_objects[m_numberOfObjects]=object;
			m_objectPoints[m_numberOfObjects]=*point;
			m_numberOfObjects++;
			if(m_debug)
				cout<<"OctreeNode: added "<<object<<" ("<<m_numberOfObjects-1<<" -> "<<m_numberOfObjects<<") point: "<<point->m_x<<" "<<point->m_y<<" "<<point->m_z<<" boundaries: x "<<m_xStart<<" "<<m_xEnd<<" y "<<m_yStart<<" "<<m_yEnd<<" z "<<m_zStart<<" "<<m_zEnd<<endl;
			return;
		}
	
		/* we can not add it because there are 8 objects already */
		/* create 8 children and move all objects in these children */

		if(m_debug)
			cout<<"OctreeNode: is full, creating children..."<<endl;
		m_children=allocator->allocate();
		int middleX=(m_xStart+m_xEnd)/2;
		int middleY=(m_yStart+m_yEnd)/2;
		int middleZ=(m_zStart+m_zEnd)/2;
		int child=0;
		m_children[child++].constructor(m_xStart,middleX-1,m_yStart,middleY-1,m_zStart,middleZ-1,m_maxPerNode,m_depth+1);
		m_children[child++].constructor(m_xStart,middleX-1,m_yStart,middleY-1,middleZ,m_zEnd,m_maxPerNode,m_depth+1);
		m_children[child++].constructor(m_xStart,middleX-1,middleY,m_yEnd,m_zStart,middleZ-1,m_maxPerNode,m_depth+1);
		m_children[child++].constructor(m_xStart,middleX-1,middleY,m_yEnd,middleZ,m_zEnd,m_maxPerNode,m_depth+1);
		m_children[child++].constructor(middleX,m_xEnd,m_yStart,middleY-1,m_zStart,middleZ-1,m_maxPerNode,m_depth+1);
		m_children[child++].constructor(middleX,m_xEnd,m_yStart,middleY-1,middleZ,m_zEnd,m_maxPerNode,m_depth+1);
		m_children[child++].constructor(middleX,m_xEnd,middleY,m_yEnd,m_zStart,middleZ-1,m_maxPerNode,m_depth+1);
		m_children[child++].constructor(middleX,m_xEnd,middleY,m_yEnd,middleZ,m_zEnd,m_maxPerNode,m_depth+1);
		
		/* add the current objects */
		/* they will be added in children because m_children != NULL */
		for(int i=0;i<m_numberOfObjects;i++){
			add(m_objectPoints+i,m_objects[i],allocator);
		}

		m_numberOfObjects=0;
	}

	if(m_debug)
		cout<<"OctreeNode Adding point in children"<<endl;
	#ifdef ASSERT
	bool someoneHasPoint=false;
	#endif
	/* ask children */
	for(int i=0;i<8;i++){
		if(m_children[i].hasPoint(point)){
			#ifdef ASSERT
			someoneHasPoint=true;
			#endif

			m_children[i].add(point,object,allocator);
		}
	}
	#ifdef ASSERT
	if(!someoneHasPoint){
		cout<<"self"<<endl;
		print();
		cout<<"Error: no one has point. "<<endl;
		point->print();
		for(int i=0;i<8;i++){
			cout<<"Children "<<i<<endl;
			m_children[i].print();
		}
	}
	assert(someoneHasPoint);
	#endif
}

void OctreeNode::getList(Vector*point,set<uint64_t>*output){
	if(!hasPoint(point))
		return;

	if(m_children==NULL){
		for(int i=0;i<m_numberOfObjects;i++){
			output->insert(m_objects[i]);
		}
	}else{
		for(int i=0;i<8;i++){
			m_children[i].getList(point,output);
		}
	}
}

bool OctreeNode::hasPoint(Vector*point){
	if(!(m_xStart<=point->m_x && point->m_x <= m_xEnd))
		return false;
	if(!(m_yStart<=point->m_y && point->m_y <= m_yEnd))
		return false;
	if(!(m_zStart<=point->m_z && point->m_z <= m_zEnd))
		return false;
	return true;
}

int OctreeNode::getObjects(){
	return m_numberOfObjects;
}

bool OctreeNode::hasChildren(){
	return m_children!=NULL;
}

void OctreeNode::print(){
	cout<<"OctreeNode depth "<<m_depth<<" boundaries: x "<<m_xStart<<" "<<m_xEnd<<" y "<<m_yStart<<" "<<m_yEnd<<" z "<<m_zStart<<" "<<m_zEnd<<endl;
}
