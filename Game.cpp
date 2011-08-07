#include "Game.h"
#include "Wall.h"
#include "Ball.h"
#include <iostream>
using namespace std;


void Game::runGame(){
	FRAMES_PER_SECOND=60;
	m_lastTicks=SDL_GetTicks();
	m_screen.constructor();

	Wall wall(200,200,300,20,30, 255,10,10);
	m_objects.push_back(&wall);
/*
	Wall wall2(400,30,300,10, 1, 10, 255, 200);
	m_objects.push_back(&wall2);
	Wall wall3(300,400,200,40, 1, 20, 20, 250);
	m_objects.push_back(&wall3);
*/
	Wall wall4(320,5,640,10, 0, 100, 200, 100);
	wall4.freeze();
	m_objects.push_back(&wall4);

	Wall wall5(320,480-5,640,10, 0, 100, 200, 100);
	wall5.freeze();
	m_objects.push_back(&wall5);

	Wall wall6(5,240,10,480, 0, 100, 200, 100);
	wall6.freeze();
	m_objects.push_back(&wall6);

	Wall wall7(640-5,240,10,480, 0, 100, 200, 100);
	wall7.freeze();
	m_objects.push_back(&wall7);


	Ball ball(400,300,30,2,40);
	m_objects.push_back(&ball);

	mainLoop();
	
	m_screen.destructor();
}

void Game::mainLoop(){
	while(1){
		getPlayerInput();
		updateGameState();
		displayGame();
	}
}

void Game::displayGame(){
	m_screen.clear();
	for(int i=0;i<(int)m_objects.size();i++){
		m_objects[i]->display(&m_screen);
	}
	m_screen.display();

	Uint32 ticks=SDL_GetTicks();
	int diff=ticks-m_lastTicks;
	m_lastTicks=ticks;
	int minimum=1000 / FRAMES_PER_SECOND;
	int left=minimum-diff;
	if(left>0){
		SDL_Delay(left);
	}
}

void Game::getPlayerInput(){

}

void Game::updateGameState(){
	for(int i=0;i<(int)m_objects.size();i++){
		m_objects[i]->update();
	}
}
