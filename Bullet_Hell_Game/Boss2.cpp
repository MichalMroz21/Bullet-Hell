#include "Boss2.h"
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstdio>

#define LEVEL_WIDTH    1280
#define LEVEL_HEIGHT    960
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define BASIC_ENEMY_SPEED_B 3
#define ENEMY_SPEED_BONUS_PER_ROUND_B 0.5
#define LICZBA_POCISKOW_MAX 12
#define BOSS2_HP 3

Boss2::Boss2()
{
	posX = 300;
	posY = 10;
	space = BASIC_ENEMY_SPEED_B;
	bulletCounter = 0;
	HP = BOSS2_HP;
	liczbaPociskowMax = LICZBA_POCISKOW_MAX + 1;
	newPosX = 0;
	newPosY = 0;
	strona = 0;
	extraX = 0;
	extraY = 0;
}

Boss2::~Boss2()
{
}


void Boss2::Reset()
{
	posX = 300;
	posY = 10;
	space = BASIC_ENEMY_SPEED_B;
	bulletCounter = 0;
	HP = BOSS2_HP;
	liczbaPociskowMax = LICZBA_POCISKOW_MAX + 1;
	newPosX = 0;
	newPosY = 0;
	strona = 0;
	extraX = 0;
	extraY = 0;
}

void Boss2::fire()
{

	if (HP > 0) {

		bulletCounter++;

		if (bulletCounter == 100) {
			bulletCounter = 0;
			extraX = 0;
			extraY = 0;
			strona = !strona;
		}

		if (HP == 1) {
			extraY += space * 5;
			extraX += space * 5;
		}
		else {
			extraY += space * 2;
			extraX += space * 3;
		}
		
		

	}

}

void Boss2::resetBulletCounter() {
	bulletCounter = 0;
}

int Boss2::getBulletCounter() {
	return bulletCounter;
}

float Boss2::getRadius()
{
	return Radius;
}

float Boss2::getAngle(int i)
{
	return angle[i];
}

int Boss2::getSpace() {
	return space;
}

float Boss2::getPosX() {
	return posX;
}

float Boss2::getPosY() {
	return posY;
}

int Boss2::getNewPosY()
{
	return newPosY;
}

int Boss2::getNewPosX()
{
    return newPosX;
}

int Boss2::getExtraX()
{
	return extraX;
}

int Boss2::getExtraY()
{
	return extraY;
}

int Boss2::getHP() {
	return HP;
}

void Boss2::changeHP(int n)
{
	HP = n;
}

int Boss2::getLiczbaPociskowMax()
{
	return liczbaPociskowMax;
}

void Boss2::changeSpace(int n) {
	space = n;
}

