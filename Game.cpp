#include "Game.h"

void Game::runGame(){
	m_screenWidth=640;
	m_screenHeight=480;
	SDL_Init( SDL_INIT_EVERYTHING );
	m_screen = SDL_SetVideoMode( m_screenWidth, m_screenHeight, 32, SDL_SWSURFACE );

	Uint32 colour;  
 
	colour = SDL_MapRGB( m_screen->format, 255, 255, 255 );

	Uint32 *pixmem32;
	for(int x=0;x<m_screenWidth;x++){
		for(int y=0;y<m_screenHeight;y++){
			pixmem32 = (Uint32*) m_screen->pixels  + y*m_screenWidth + x;
			*pixmem32 = colour;
		}
	}

	mainLoop();
	
	SDL_Quit();
}

void Game::mainLoop(){
	while(1){
		getPlayerInput();
		updateGameState();
		displayGame();
	}
}

void Game::displayGame(){
	SDL_Flip(m_screen );
}

void Game::getPlayerInput(){

}

void Game::updateGameState(){

}
