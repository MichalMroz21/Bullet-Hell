#ifndef Player_h
#define Player_h

#include "Bullet.h"
#include "Timing.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

class Player {


public:
	Player();
	~Player();

	int getPositionX();
	int getPositionY();
	void moveUp(SDL_Rect* camera);
	void moveDown(SDL_Rect* camera);
	void moveRight(SDL_Rect* camera);
	void moveLeft(SDL_Rect* camera);
	void fire(Bullet* bullet);
	void changeHP(int n);
	int getHP();
	void addBullet(Bullet* bullet);
	void reset(Bullet* bullet, int gameReset);

private:
	int posX;
	int posY;
	int bulletCount;
	int space;
	int HP;
	
};






#endif 