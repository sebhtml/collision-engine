
#ifndef _Game_H
#define _Game_H

#include <vector>
#include "Grid.h"
#include "Object.h"
#include "Screen.h"
#include "Octree.h"

using namespace std;

class Game{
	Octree m_octree;
	Grid m_grid;
	Uint32 m_lastTicks;
	int FRAMES_PER_SECOND;
	Screen m_screen;
	vector<Object*> m_objects;
	vector<Object*> m_moving;

	void mainLoop();
	void getPlayerInput();
	void updateGameState();
	void displayGame();
	void addObject(Object*object);
public:
	void runGame();
};

#endif
