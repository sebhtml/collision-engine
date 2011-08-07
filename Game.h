
#ifndef _Game_H
#define _Game_H

#include <vector>
#include "Object.h"
#include "Screen.h"

using namespace std;

class Game{
	Uint32 m_lastTicks;
	int FRAMES_PER_SECOND;
	Screen m_screen;
	vector<Object*> m_objects;

	void mainLoop();
	void getPlayerInput();
	void updateGameState();
	void displayGame();
public:
	void runGame();
};

#endif
