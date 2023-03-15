#define _USE_MATH_DEFINES
#define TIME_STRING_SIZE 10
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define LEVEL_WIDTH    1280
#define LEVEL_HEIGHT    960
#define MAX_ENEMIES     100
#define MAX_BOSSES		100
#define MAX_HEALTH_PACKETS     3
#define MAX_HEALTH             5
#define MAX_BULLETS		100
#define BASIC_ENEMY_SPEED_B 3
#define ENEMY_SPEED_BONUS_PER_ROUND_B 0.5
#define BASIC_NUMBER_OF_ENEMIES 5
#define BONUS_ENEMIES_PER_ROUND 1

#include<math.h>
#include<stdio.h>
#include<string.h>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include "Player.h"
#include "Timing.h"
#include "Game.h"
#include "Enemy.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Health.h"


#define FPS             60
#define FPS_DELAY       1000 / FPS //jedna pêtla while - jedna klatka ma siê odbywaæ w takim czasie zale¿nym od zmiennej FPS.


void DrawString(SDL_Surface *screen, int x, int y, char *text, SDL_Surface *charset, int size) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	for(int i=0; i<size; i++) {
		c = text[i]&255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		};
	};


void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = (sprite->w);
	dest.h = (sprite->h);
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	};




#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {

	srand(time(NULL));

	Game* game = new Game();
	Timing* timer = new Timing();
	Player* player = new Player();

	Bullet* bullet = new Bullet[MAX_BULLETS];

	Enemy enemies[MAX_ENEMIES];
	Boss1 boss1[MAX_BOSSES];
	Boss2 boss2[MAX_BOSSES];
	Health health[MAX_HEALTH_PACKETS];

	SDL_Rect camera = { 0,0, SCREEN_WIDTH, (SCREEN_HEIGHT) * (6.0 / 7.0) };

	int timeStrzal = -1;
	int timeStrzalGracz = -1;

	long int frameStart = 0;
	int timeOfFrame = 0;
	long int frameStartMenu = 0;
	int timeOfFrameMenu = 0;

	static int* currentTimeEvent = new int(-1);
	static int* currentTimeEvent2 = new int(-1);
	static int* currentTimeEvent3 = new int(-1);
	static int* currentTimeEvent4 = new int(-1);

	game->init("Bullet_Hell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, BASIC_NUMBER_OF_ENEMIES, 1); //3 od lewej - fullscreen(0 - brak, 1 - jest), ostatni - ustawienie wartoœci obecnego poziomu

	while (game->running()) {

		if (game->getIsMenu() == 1) {

			frameStartMenu = 0;
			timeOfFrameMenu = 0;
			bool firstIt = 1;
			game->changeSelect(1);
			static int* currentTimeEvent3 = new int(-1);
			int MenuStartTime = SDL_GetTicks();

			while (game->getIsMenu()) {

				
				game->handleEventsMenu(currentTimeEvent3, game, enemies, player, timer, bullet, &camera, MenuStartTime, health, boss1, boss2);
				game->renderMenu();

				timeOfFrameMenu = SDL_GetTicks() - frameStartMenu;

				if (FPS_DELAY > timeOfFrameMenu) {
					SDL_Delay(FPS_DELAY - timeOfFrameMenu);
				}

			}
		}

		if (game->getIsGameover() == 1) {
			frameStartMenu = 0;
			timeOfFrameMenu = 0;
			game->changeSelect(1);
			static int* currentTimeEvent3 = new int(-1);
			int GameOverStartTime = SDL_GetTicks();

			while (game->getIsGameover()) {

				frameStartMenu = SDL_GetTicks();
				game->handleEventsGameover(currentTimeEvent3, game, enemies, player, timer, bullet, &camera, GameOverStartTime, health, boss1, boss2);
				game->renderGameover();

				timeOfFrameMenu = SDL_GetTicks() - frameStartMenu;

				if (FPS_DELAY > timeOfFrameMenu) {
					SDL_Delay(FPS_DELAY - timeOfFrameMenu);
				}

			}
		}
		
		frameStart = SDL_GetTicks();

		if (game->handleEvents(player, &camera, bullet, currentTimeEvent)) {
			
			for (int i = 0; i < MAX_ENEMIES; i++) {
				enemies[i].Reset();
			}

			for (int i = 0; i < game->getHowManyBosses1(); i++) {
				boss1[i].Reset();
			}
			game->changeHowManyBosses1(game->getLevel() % 2 ? game->getLevel() / 2 + 1 : 0);

			for (int i = 0; i < game->getHowManyBosses2(); i++) {
				boss2[i].Reset();
			}
			game->changeHowManyBosses2(game->getLevel() % 2 ? 0 : 1);

			for (int i = 0; i < MAX_HEALTH_PACKETS; i++) {
				health[i].Reset();
			}

			player->reset(bullet, 1);
			timer->reset();
			game->changePlayerhit(0);
			game->changeMultiplier(1);
			game->changeScore(0);
			camera = { 0,0, SCREEN_WIDTH, ((SCREEN_HEIGHT*6)/7) };
			game->changeStartNumberOfEnemies(BASIC_NUMBER_OF_ENEMIES);
			game->changeNumberOfEnemies(BASIC_NUMBER_OF_ENEMIES);
			game->changeLevel(1);
			long int frameStart = 0;
			int timeOfFrame = 0;
			int timeStrzal = -1;
			
		}

		if (game->getNumberOfEnemies() == 0) {

			bool flag = 1;

			for (int i = 0; i < game->getHowManyBosses1(); i++) {
				if (boss1[i].getHP() > 0) flag = 0;
			}
			for (int i = 0; i < game->getHowManyBosses2(); i++) {
				if (boss2[i].getHP() > 0) flag = 0;
			}

			if (flag) {

				game->changeLevel(game->getLevel() + 1);

				for (int i = 0; i < MAX_ENEMIES; i++) {
					enemies[i].Reset();
					enemies[i].changeSpace(BASIC_ENEMY_SPEED_B + game->getLevel() * ENEMY_SPEED_BONUS_PER_ROUND_B);
				}

				for (int i = 0; i < game->getHowManyBosses1(); i++) {
					boss1[i].Reset();
				}
				game->changeHowManyBosses1(game->getLevel() % 2 ? game->getLevel() / 2 + 1 : 0);

				game->changeHowManyBosses2(game->getLevel() % 2 ? 0 : 1);

				for (int i = 0; i < game->getHowManyBosses2(); i++) {
					boss2[i].Reset();
				}

				for (int i = 0; i < MAX_HEALTH_PACKETS; i++) {
					health[i].Reset();
				}

				for (int i = 0; i < MAX_HEALTH_PACKETS; i++) {
					health[i].Reset();
				}

				player->reset(bullet, 0);
				timer->reset();
				camera = { 0, 0, SCREEN_WIDTH, ((SCREEN_HEIGHT * 6) / 7) };

				game->changeStartNumberOfEnemies(BASIC_NUMBER_OF_ENEMIES + ((game->getLevel() - 1) * BONUS_ENEMIES_PER_ROUND));
				game->changeNumberOfEnemies(BASIC_NUMBER_OF_ENEMIES + ((game->getLevel() - 1) * BONUS_ENEMIES_PER_ROUND));

				long int frameStart = 0;
				int timeOfFrame = 0;
				int timeStrzal = -1;

			}

		}

		game->update(timer->convertTimeToString(timer->getCurrentTime()), player->getPositionX(), player->getPositionY(), &camera, enemies, game->getStartNumberOfEnemies(), player, bullet, currentTimeEvent2, health, boss1, currentTimeEvent3, boss2, currentTimeEvent4);
		game->updateTimer(timer, player, boss1, boss2);
		game->render(player);

		if (frameStart - timeStrzal > 10) {

			for (int i = 0; i < game->getStartNumberOfEnemies(); i++) {
				enemies[i].fire();
			}
			
			for (int i = 0; i < game->getHowManyBosses1(); i++) {
				boss1[i].fire();
			}

			for (int i = 0; i < game->getHowManyBosses2(); i++) {
				boss2[i].fire();
			}
			
			timeStrzal = SDL_GetTicks();
		}
		if (frameStart - timeStrzalGracz > 10) {
			player->fire(bullet);
			timeStrzalGracz = SDL_GetTicks();
		}

		timeOfFrame = SDL_GetTicks() - frameStart;

		if (FPS_DELAY > timeOfFrame) {
			SDL_Delay(FPS_DELAY - timeOfFrame);
		}

		
	}

	game->closeGame();

	return 0;
}
