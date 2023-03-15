#include "Bullet.h"

Bullet::Bullet(){
	 startingPosX = 0;
	 startingPosY = 0;
	 currentPosX = 0;
	 currentPosY = 0;
	 exists = 0;
}

Bullet::~Bullet(){
	
}

int Bullet::CurrentPosX(){
	return currentPosX;
}

int Bullet::CurrentPosY(){
	return currentPosY;
}

int Bullet::StartingPosX(){
	return startingPosX;
}

int Bullet::StartingPosY(){
	return startingPosY;
}

int Bullet::Exists(){
	return exists;
}
