#include "Player.h"
#include "Bullet.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define LEVEL_WIDTH    1280
#define LEVEL_HEIGHT    960
#define PLAYER_SIZE		 38
#define MAX_HEALTH_PACKETS     3
#define MAX_HEALTH             5
#define MAX_BULLETS			100
#define BASIC_PLAYER_BULLET_SPEED 10
#define PLAYER_MOVEMENT_SPEED 3
#define PLAYER_BULLET_DISTANCE 150

#include <stdio.h>
#include <cmath>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


SDL_Rect* camera;
Player::Player(){
	posX = SCREEN_WIDTH / 2;
	posY = (SCREEN_HEIGHT - (SCREEN_HEIGHT / 7)) / 2;
	space = BASIC_PLAYER_BULLET_SPEED;
	HP = MAX_HEALTH;
	bulletCount = 0;
}

Player::~Player(){

}

int Player::getPositionX(){
	return posX;
}
int Player::getPositionY(){
	return posY;
}

void Player::moveUp(SDL_Rect* camera){
	
	if (camera->y - PLAYER_MOVEMENT_SPEED > 0) {
		posY -= PLAYER_MOVEMENT_SPEED;
		camera->y = camera->y - PLAYER_MOVEMENT_SPEED;
		printf("Camera Y: %d\n", camera->y);
		printf("Y: %d\n", posY);
	}
	
}

void Player::moveDown(SDL_Rect* camera){
	
	if (camera->y + PLAYER_MOVEMENT_SPEED + (SCREEN_HEIGHT) * (6.0 / 7.0) < LEVEL_HEIGHT) {
		posY += PLAYER_MOVEMENT_SPEED;
		camera->y = camera->y + PLAYER_MOVEMENT_SPEED;
		printf("Camera Y: %d\n", camera->y);
		printf("Y: %d\n", posY);
	}
}

void Player::moveRight(SDL_Rect* camera){
	if (camera->x + PLAYER_MOVEMENT_SPEED + SCREEN_WIDTH < LEVEL_WIDTH) {
		posX += PLAYER_MOVEMENT_SPEED;
		camera->x = camera->x + PLAYER_MOVEMENT_SPEED;
		printf("Camera X: %d\n", camera->x);
		printf("X: %d\n", posX);
	}
}

void Player::moveLeft(SDL_Rect* camera){

	if (camera->x - PLAYER_MOVEMENT_SPEED > 0) {
		posX -= PLAYER_MOVEMENT_SPEED;
		camera->x = camera->x - PLAYER_MOVEMENT_SPEED;
		printf("Camera X: %d\n", camera->x);
		printf("X: %d\n", posX);
	}
}

void Player::fire(Bullet* bullet) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullet[i].exists) {
			if (i % 2) {
				bullet[i].currentPosY += BASIC_PLAYER_BULLET_SPEED;
				bullet[i].currentPosX +=  0;
			}
			else {
				bullet[i].currentPosY -= BASIC_PLAYER_BULLET_SPEED;
				bullet[i].currentPosX -=  0;
			}
			if (abs(bullet[i].currentPosY - bullet[i].startingPosY) >= (PLAYER_BULLET_DISTANCE* BASIC_PLAYER_BULLET_SPEED)) {
				bullet[i].exists = 0;
				bulletCount--;
			}
		}
	}
}

void Player::changeHP(int n){
	HP = n;
}

int Player::getHP(){
	return HP;
}

void Player::addBullet(Bullet* bullet){
		
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!(bullet[i].exists)) {
				bullet[i].exists = 1;
				bullet[i].startingPosX = posX;
				bullet[i].startingPosY = posY;
				bullet[i].currentPosX = posX;
				bullet[i].currentPosY = posY;
				bulletCount++;
				break;
			}
		}
	
}

void Player::reset(Bullet* bullet, int gameReset){
	posX = SCREEN_WIDTH / 2;
	posY = (SCREEN_HEIGHT - (SCREEN_HEIGHT / 7)) / 2;
	bulletCount = 0;
	if(gameReset) space = BASIC_PLAYER_BULLET_SPEED;
	else {
	}
	if(gameReset) HP = MAX_HEALTH;
	for (int i = 0; i < MAX_BULLETS; i++) {
		bullet[i].exists = 0;
		bullet[i].startingPosX=0;
		bullet[i].startingPosY=0;
		bullet[i].currentPosX=0;
		bullet[i].currentPosY=0;
	}
}
