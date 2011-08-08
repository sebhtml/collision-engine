
#ifndef _Grid
#define _Grid

#include <stdint.h>
#include <vector>
using namespace std;

class Grid{
	uint64_t m_currentIdentifier;
	vector<uint64_t> m_identifiers;
public:
	void addObject(uint64_t identifier);
	void getNearbyObjects(uint64_t identifier,vector<uint64_t>*out);
	uint64_t getNextObjectIdentifier();
	Grid();
};

#endif
