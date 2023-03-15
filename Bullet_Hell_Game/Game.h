#ifndef Game_h
#define Game_h

#include <stdio.h>
#include "Player.h"
#include "Enemy.h"
#include "Health.h"
#include "Boss1.h"
#include "Boss2.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen, int liczbaprzeciwnikow, int level);

	bool handleEvents(Player* p, SDL_Rect* camera, Bullet* bullet, static int* currentTimeEvent);
	void handleEventsMenu(int* currentTimeEvent3, Game* game, Enemy* enemies, Player* player, Timing* timer, Bullet* bullet, SDL_Rect* camera, int menustart, Health* health, Boss1* boss1, Boss2* boss2);
	void update(char* text, int posX, int posY, SDL_Rect* camera, Enemy* enemies, int number_of_enemies, Player* p, Bullet* Bullet, static int* currentTimeEvent, Health* health, Boss1* boss1, static int* boss1hit, Boss2* boss2, static int* boss2hit);
	void render(Player* player);
	void renderMenu();
	void renderGameover();
	void handleEventsGameover(int* currentTimeEvent3, Game* game, Enemy* enemies, Player* player, Timing* timer, Bullet* bullet, SDL_Rect* camera, int gameoverstart, Health* health, Boss1* boss1, Boss2* boss2);
	void closeGame(bool b=1);
	SDL_Surface* getScreen();
	SDL_Surface* getInfo();
	SDL_Surface* getCharset();
	void changeNumberOfEnemies(int n);
	int getNumberOfEnemies();
	int getStartNumberOfEnemies();
	int getLevel();
	int getPlayerhit();
	void changePlayerhit(int n);
	bool getIsMenu();
	bool getIsGameover();
	int getSelect();
	bool getIsInvis();
	int getMultiplier();
	int getScore();
	void changeMultiplier(int n);
	void changeScore(int n);
	void changeSelect(int n);
	void changeIsMenu(bool b);
	void changeLevel(int n);
	void changeIsGameover(bool b);
	void changeIsInvis(bool b);
	void changeStartNumberOfEnemies(int n);
	void clearScreen(int width, int height);
	void clearInfo(int width, int height);
	void updateTimer(Timing* timer, Player* p, Boss1* boss1, Boss2* boss2);
	int getHowManyBosses1();
	int getHowManyBosses2();
	void changeHowManyBosses1(int n);
	void changeHowManyBosses2(int n);

	void zeros(char* tab, int a, int b, bool nulls=0);
	void Game::convertToChar(char* tab, int num, int start);
	void Game::AddString(char* target, char* add, int begin, int end);

	bool checkCollision(SDL_Rect a, SDL_Rect b);
	bool running();
	
private:

	int liczbaPrzeciwnikow;
	int startowaLiczbaPrzeciwnikow;
	bool isRunning;
	int level;
	int select;
	bool isMenu;
	bool isGameover;
	bool isInvis;
	int playerHit;
	int score;
	int multiplier;
	int howManyBosses1;
	int howManyBosses2;
	
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Surface* grade;
	SDL_Surface* screen;
	SDL_Surface* menu;
	SDL_Surface* gameover;
	SDL_Surface* info;
	SDL_Surface* charset;
	SDL_Surface* eti;
	SDL_Surface* health;
	SDL_Surface* enemy_S;
	SDL_Surface* Boss1_S;
	SDL_Surface* Boss2_S;
	SDL_Surface* bullet;
	SDL_Surface* background;
};

#endif 