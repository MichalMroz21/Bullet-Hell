#include "Health.h"
#include <time.h>
#include <ctime>
#include <cstdlib>

#define LEVEL_WIDTH    1280
#define LEVEL_HEIGHT    960
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

Health::Health(){
	posX = (rand() % (SCREEN_WIDTH - 100)) + SCREEN_WIDTH / 2;
	posY = (rand() % (SCREEN_HEIGHT)) + 230;
	exists = 1;
}

Health::~Health(){
}

int Health::getPosX(){
	return posX;
}

int Health::getPosY(){
	return posY;
}

int Health::getExists(){
	return exists;
}

void Health::changeExists(int n){
	exists = n;
}

void Health::Reset(){
	posX = (rand() % (SCREEN_WIDTH - 100)) + SCREEN_WIDTH / 2;
	posY = (rand() % (SCREEN_HEIGHT)) + 230;
	exists = 1;
}
