#include "Game.h"
#include "Wall.h"
#include "Grid.h"
#include "Ball.h"
#include <iostream>
using namespace std;


void Game::runGame(){
	FRAMES_PER_SECOND=60;
	m_lastTicks=SDL_GetTicks();
	m_screen.constructor();
/*
	Wall wall(200,200,300,20,30, 255,10,10);
	addObject(&wall);
*/
/*
	Wall wall2(400,30,300,10, 1, 10, 255, 200);
	m_objects.push_back(&wall2);
	Wall wall3(300,400,200,40, 1, 20, 20, 250);
	m_objects.push_back(&wall3);
*/
	Wall wall4(320,5,640,10, 0, 100, 200, 100);
	wall4.freeze();
	addObject(&wall4,true);

	Wall wall5(320,480-5,640,10, 0, 100, 200, 100);
	wall5.freeze();
	addObject(&wall5,true);

	Wall wall6(5,240,10,480, 0, 100, 200, 100);
	wall6.freeze();
	addObject(&wall6,true);

	Wall wall7(640-5,240,10,480, 0, 100, 200, 100);
	wall7.freeze();
	addObject(&wall7,true);

	Ball ball(400,300,30,1,270);
	addObject(&ball,false);

	Ball ball2(200,300,50,1,90);
	addObject(&ball2,false);
	Ball ball3(500,100,10,2,280);
	addObject(&ball3,false);
/*
	Ball ball4(500,100,10,4,0);
	addObject(&ball4);
*/
	vector<Ball> cache;
	cache.reserve(512);
	
	for(int i=0;i<400;i++){
		Ball ballX(400,200,i%40+3,i%3+2,4*i%360);
		cache.push_back(ballX);
		addObject(&(cache[cache.size()-1]),false);
	}

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
		//cout<<"To process: "<<collisions.size()<<endl;
		for(int j=0;j<(int)collisions.size();j++){
			m_objects[i]->processCollision(m_objects[collisions[j]]);
		}
		m_objects[i]->update();
	}
}

void Game::addObject(Object*object,bool addInGrid){
	object->setObjectIdentifier(m_grid.getNextObjectIdentifier());
	m_objects.push_back(object);
	if(addInGrid)
		m_grid.addObject(object->getObjectIdentifier());
}
