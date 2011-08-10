/* 
	Author: Sébastien Boisvert
	Year: 2011
*/

#include "Game.h"
#include <SDL/SDL.h>
#include "Wall.h"
#include "Ball.h"
#include <iostream>

using namespace std;

void Game::runGame(){
	m_display=true;
	int width=640;
	int height=480;
	int depth=1000;

	int precision=1000;
	int gameWidth=width*precision;
	int gameHeight=height*precision;
	int gameDepth=depth*precision;

	m_octree.constructor(gameWidth,gameHeight,gameDepth);

	FRAMES_PER_SECOND=60;
	m_lastTicks=SDL_GetTicks();
	m_screen.constructor(width,height,precision);

	int radius=10*precision;

	vector<Ball> cache;
	cache.reserve(512);
	
	int borderRadius=radius;

	for(int i=3*borderRadius;i<gameWidth-borderRadius*3;i+=borderRadius*4+3){
		for(int j=3*borderRadius;j<gameHeight-borderRadius*3;j+=borderRadius*4+2){
			Vector center2(i,j,0);
			Vector direction2(1000,1000,0);
			Ball ball2(&center2,borderRadius,&direction2);
			cache.push_back(ball2);
			addObject(&(cache[cache.size()-1]));
		}
	}


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

	m_screen.startBackground();

	for(int i=0;i<(int)m_background.size();i++){
		m_background[i]->display(&m_screen);
	}
	m_screen.endBackground();

	mainLoop();
	
	m_screen.destructor();
}

void Game::mainLoop(){
	cout<<m_objects.size()<<" objects"<<endl;
	Uint32 startTime = SDL_GetTicks();
	int frames=0;
	while(1){
		getPlayerInput();
		updateGameState();
		if(m_display)
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
	m_screen.displayBackground();
	for(int i=0;i<(int)m_moving.size();i++){
		m_moving[i]->display(&m_screen);
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
	//cout<<"Moving objects: "<<m_moving.size()<<endl;

	for(int i=0;i<(int)m_moving.size();i++){
		if(!m_objects[i]->isMoving())
			continue;
		set<uint64_t> objects;
		Vector center;
		int radius;
		m_moving[i]->getGeometry(&center,&radius);
		m_octree.getList(&center,radius,&objects);

		//cout<<"Objects to check: "<<objects.size()<<endl;
		if(objects.size() == 0)
			continue;

		for(set<uint64_t>::iterator j=objects.begin();j!=objects.end();j++){
			m_objects[i]->processCollision(m_objects[(*j)]);
		}
	}
	for(int i=0;i<(int)m_moving.size();i++){
		m_objects[i]->update(&m_octree);
	}
}

void Game::addObject(Object*object){
	object->setObjectIdentifier(m_objects.size());
	m_objects.push_back(object);
	if(object->isMoving())
		m_moving.push_back(object);
	else
		m_background.push_back(object);

	Vector center;
	int radius;
	object->getGeometry(&center,&radius);
	m_octree.add(&center,radius,object->getObjectIdentifier());
}
