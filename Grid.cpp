
#include "Grid.h"

Grid::Grid(){
	m_currentIdentifier=0;
}

void Grid::addObject(uint64_t identifier){
	m_identifiers.push_back(identifier);
}

void Grid::getNearbyObjects(uint64_t identifier,vector<uint64_t>*out){
	for(int i=0;i<(int)m_identifiers.size();i++){
		if(m_identifiers[i]!=identifier)
			out->push_back(m_identifiers[i]);
	}
}

uint64_t Grid::getNextObjectIdentifier(){
	return m_currentIdentifier++;
}
