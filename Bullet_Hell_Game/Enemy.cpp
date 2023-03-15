#include "Enemy.h"
#include <time.h>
#include <ctime>
#include <cstdlib>

#define LEVEL_WIDTH    1280
#define LEVEL_HEIGHT    960
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define BASIC_ENEMY_SPEED_B 3
#define ENEMY_SPEED_BONUS_PER_ROUND_B 0.5
Enemy::Enemy(){
	
	posX = (rand() % (SCREEN_WIDTH - 100)) + SCREEN_WIDTH / 2;
	posY = (rand() % (LEVEL_HEIGHT - 200)) + 50;
	space = BASIC_ENEMY_SPEED_B;
	bulletCounter = 0;
	firstBulletX = 0;
	firstBulletY = 0;
	czyTrafiony = 0;
}

void Enemy::Reset() {
	posX = (rand() % (SCREEN_WIDTH - 100)) + SCREEN_WIDTH / 2;
	posY = (rand() % (LEVEL_HEIGHT - 200)) + 50;
	space = BASIC_ENEMY_SPEED_B;
	bulletCounter = 0;
	firstBulletX = 0;
	firstBulletY = 0;
	czyTrafiony = 0;
}

void Enemy::fire() {
	
	if (!(czyTrafiony)) {

		bulletCounter++;

		if (bulletCounter == 100) {
			bulletCounter = 0;
			firstBulletX = 0;
			firstBulletY = 0;
		}

		firstBulletX += space;
		firstBulletY += space;
	}
	
}

Enemy::~Enemy(){
}

void Enemy::resetBulletCounter() {
	bulletCounter = 0;
}

int Enemy::getBulletCounter() {
	return bulletCounter;
}

int Enemy::getFirstBulletX() {
	return firstBulletX;
}

int Enemy::getFirstBulletY() {
	return firstBulletY;
}

int Enemy::getSpace() {
	return space;
}

int Enemy::getPosX(){
	return posX;
}

int Enemy::getPosY(){
	return posY;
}

int Enemy::getCzyTrafiony() {
	return czyTrafiony;
}

void Enemy::changeSpace(int n){
	space = n;
}

void Enemy::trafiony() {
	czyTrafiony = 1;
}

