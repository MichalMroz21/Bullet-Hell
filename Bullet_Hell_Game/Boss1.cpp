#include "Boss1.h"
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
#define BOSS1_HP 3

Boss1::Boss1()
{
	posX = float((rand() % (SCREEN_WIDTH - 100)) + SCREEN_WIDTH / 2);
	posY = float((rand() % (LEVEL_HEIGHT - 200)) + 50);
	space = BASIC_ENEMY_SPEED_B;
	bulletCounter = 0;
	HP = BOSS1_HP;
	liczbaPociskowMax = LICZBA_POCISKOW_MAX+1;
}

Boss1::~Boss1()
{
}


void Boss1::Reset()
{
	posX = (rand() % (SCREEN_WIDTH - 100)) + SCREEN_WIDTH / 2;
	posY = (rand() % (LEVEL_HEIGHT - 200)) + 50;
	space = BASIC_ENEMY_SPEED_B;
	bulletCounter = 0;
	HP = BOSS1_HP;
	liczbaPociskowMax = LICZBA_POCISKOW_MAX+1;
}

void Boss1::fire()
{

	if (HP > 0) {

		bulletCounter++;

		if (bulletCounter == 100) {
			bulletCounter = 0;
		}

			float radius = (float)bulletCounter * (float)space * 1.0;
			Radius = radius;

			for (int i = 0; i <= LICZBA_POCISKOW_MAX; i++) {
				angle[i] = i * 30;
			}

	}

}

void Boss1::resetBulletCounter() {
	bulletCounter = 0;
}

int Boss1::getBulletCounter() {
	return bulletCounter;
}

float Boss1::getRadius()
{
	return Radius;
}

float Boss1::getAngle(int i)
{
	return angle[i];
}

int Boss1::getSpace() {
	return space;
}

float Boss1::getPosX() {
	return posX;
}

float Boss1::getPosY() {
	return posY;
}

int Boss1::getHP() {
	return HP;
}

void Boss1::changeHP(int n)
{
	HP = n;
}

int Boss1::getLiczbaPociskowMax()
{
	return liczbaPociskowMax;
}

void Boss1::changeSpace(int n) {
	space = n;
}

