#include "Game.h"
#include <SDL/SDL.h>
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

	int radius=10*precision;

	Vector center(gameWidth/2-200*precision,gameHeight/2-100*precision,0);
	Vector direction(2200,120,0);
	Ball ball(&center,radius,&direction);
	addObject(&ball);

	Vector center0(gameWidth/2-200*precision,gameHeight/2+100*precision,0);
	Vector direction0(-4200,120,0);
	Ball ball0(&center0,radius,&direction0);
	addObject(&ball0);

	Vector center2(gameWidth/2+200*precision,gameHeight/2-100*precision,0);
	Vector direction2(-2120,-20,0);
	Ball ball2(&center2,radius,&direction2);
	addObject(&ball2);

	Vector center3(gameWidth/2+200*precision,gameHeight/2+100*precision,0);
	Vector direction3(-222,-2000,0);
	Ball ball3(&center3,radius,&direction3);
	addObject(&ball3);

	vector<Ball> cache;
	cache.reserve(512);

	int borderRadius=radius;
	for(int i=2*borderRadius;i<gameWidth;i+=borderRadius*3){
		Vector center2(i,0,0);
		Vector direction2(0,0,0);
		Ball ball2(&center2,borderRadius,&direction2);
		cache.push_back(ball2);
		addObject(&(cache[cache.size()-1]));
		//cout<<"Adding border at "<<i<<" "<<borderRadius<<" radius "<<borderRadius<<endl;
	}

	for(int i=2*borderRadius;i<gameWidth;i+=borderRadius*3){
		Vector center2(i,gameHeight,0);
		Vector direction2(0,0,0);
		Ball ball2(&center2,borderRadius,&direction2);
		cache.push_back(ball2);
		addObject(&(cache[cache.size()-1]));
		//cout<<"Adding border at "<<i<<" "<<borderRadius<<" radius "<<borderRadius<<endl;
	}



	for(int i=borderRadius;i<gameHeight;i+=borderRadius*3){
		Vector center2(0,i,0);
		Vector direction2(0,0,0);
		Ball ball2(&center2,borderRadius,&direction2);
		cache.push_back(ball2);
		addObject(&(cache[cache.size()-1]));
		//cout<<"Adding border at "<<i<<" "<<borderRadius<<" radius "<<borderRadius<<endl;
	}

	for(int i=borderRadius;i<gameHeight;i+=borderRadius*3){
		Vector center2(gameWidth,i,0);
		Vector direction2(0,0,0);
		Ball ball2(&center2,borderRadius,&direction2);
		cache.push_back(ball2);
		addObject(&(cache[cache.size()-1]));
		//cout<<"Adding border at "<<i<<" "<<borderRadius<<" radius "<<borderRadius<<endl;
	}



	mainLoop();
	
	m_screen.destructor();
}

void Game::mainLoop(){
	Uint32 startTime = SDL_GetTicks();
	int frames=0;
	while(1){
		getPlayerInput();
		updateGameState();
		displayGame();
		frames++;
		Uint32 current=SDL_GetTicks();
		if(current>startTime+1000){
			float fps = ( frames/(float)(current - startTime) )*1000;
			startTime=current;
			cout<<"FPS= "<<fps<<endl;
			frames=0;
		}
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
	for(int i=0;i<(int)m_moving.size();i++){
		if(!m_objects[i]->isMoving())
			continue;
		vector<uint64_t> collisions;
		m_grid.getNearbyObjects(m_objects[i]->getObjectIdentifier(),&collisions);
		for(int j=0;j<(int)collisions.size();j++){
			//cout<<" objects to test: "<<collisions.size()<<endl;
			m_objects[i]->processCollision(m_objects[collisions[j]]);
		}
	}
	for(int i=0;i<(int)m_moving.size();i++){
		m_objects[i]->update();
	}
}

void Game::addObject(Object*object){
	object->setObjectIdentifier(m_grid.getNextObjectIdentifier());
	m_objects.push_back(object);
	m_grid.addObject(object->getObjectIdentifier());
	if(object->isMoving())
		m_moving.push_back(object);
}
