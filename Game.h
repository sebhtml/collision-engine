/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#ifndef _Game_H
#define _Game_H

#include <vector>
#include "Object.h"
#include "Screen.h"
#include "Octree.h"

using namespace std;

class Game{
	bool m_running;
	bool m_display;
	vector<Object*> m_background;
	Octree m_octree;
	Uint32 m_lastTicks;
	int m_gameIterationsPerSecond;
	Screen m_screen;
	vector<Object*> m_objects;
	vector<Object*> m_moving;

	void mainLoop();
	void getPlayerInput(SDL_Event*event);
	void updateGameState();
	void displayGame();
	void addObject(Object*object);
public:
	void runGame();
};

#endif
