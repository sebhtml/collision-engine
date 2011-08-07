
#include <SDL/SDL.h>

class Game{
	int m_screenWidth;
	int m_screenHeight;
	SDL_Surface*m_screen;

	void mainLoop();
	void getPlayerInput();
	void updateGameState();
	void displayGame();
public:
	void runGame();
};
