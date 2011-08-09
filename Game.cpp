#include "Game.h"
#include "Wall.h"
#include "Grid.h"
#include "Ball.h"
#include <iostream>
using namespace std;


void Game::runGame(){
	int gameWidth=640000;
	int gameHeight=480000;
	int width=640;
	int height=480;
	int precision=gameWidth/width;
	FRAMES_PER_SECOND=60;
	m_lastTicks=SDL_GetTicks();
	m_screen.constructor(width,height,precision);

	Vector center(gameWidth/2-100*precision,gameHeight/2,0);
	Vector direction(120,70,0);
	Ball ball(&center,50*precision,&direction);
	addObject(&ball);

	Vector center2(gameWidth/2+50*precision,gameHeight/2,0);
	Vector direction2(-110,-10,0);
	Ball ball2(&center2,50*precision,&direction2);
	addObject(&ball2);

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
		vector<uint64_t> collisions;
		m_grid.getNearbyObjects(m_objects[i]->getObjectIdentifier(),&collisions);
		for(int j=0;j<(int)collisions.size();j++){
			m_objects[i]->processCollision(m_objects[collisions[j]]);
		}
	}
	for(int i=0;i<(int)m_objects.size();i++){
		m_objects[i]->update();
	}
}

void Game::addObject(Object*object){
	object->setObjectIdentifier(m_grid.getNextObjectIdentifier());
	m_objects.push_back(object);
	m_grid.addObject(object->getObjectIdentifier());
}
