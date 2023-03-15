#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Health.h"
#include <cmath>

#define TIME_STRING_SIZE 10
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define LEVEL_WIDTH    1280
#define LEVEL_HEIGHT    960
#define BULLET_SIZE		15
#define HEALTH_SIZE		18
#define PLAYER_SIZE		38
#define MAX_ENEMIES    100
#define MAX_HEALTH_PACKETS     3
#define MAX_HEALTH             5
#define MAX_BULLETS 100
#define INVIS_TIME 1500
#define GAME_OVER_DELAY 1200
#define BASIC_PLAYER_BULLET_SPEED 10
#define BASIC_ENEMY_SPEED_B 3
#define ENEMY_SPEED_BONUS_PER_ROUND_B 0.5
#define BASIC_NUMBER_OF_ENEMIES 5
#define BONUS_ENEMIES_PER_ROUND 1
#define BASIC_NUMBER_OF_BOSSES1 1
#define BOSS1_HP 3
#define BOSS2_HP 3


void DrawString(SDL_Surface* screen, int x, int y, char* text, SDL_Surface* charset, int size);
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);


Game::Game() {
	
}
Game::~Game() {

}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen, int liczbaprzeciwnikow, int level){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL Initialize Error: %s\n", SDL_GetError());
		isRunning = false;
	}
	else {

		window = SDL_CreateWindow(title, xPos, yPos, width, height, (fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN));
		screen = SDL_CreateRGBSurface(0, width, (height - (height/7)), 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		background = SDL_LoadBMP("./background.bmp");
		menu = SDL_LoadBMP("./menu.bmp");
		gameover = SDL_LoadBMP("./gameover.bmp");
		select = 1;
		isMenu = 1;
		multiplier = 1;
		score = 0;
		isGameover = 0;
		playerHit = 0;
		howManyBosses1 = BASIC_NUMBER_OF_BOSSES1;
		howManyBosses2 = 0;
		grade = SDL_LoadBMP("./D.bmp");
		info = SDL_CreateRGBSurface(0, width, (height/7), 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		charset = SDL_LoadBMP("./cs8x8.bmp");
		eti = SDL_LoadBMP("./eti.bmp");
		health = SDL_LoadBMP("./Health.bmp");
		enemy_S = SDL_LoadBMP("./enemy.bmp");
		Boss1_S = SDL_LoadBMP("./Boss1.bmp");
		Boss2_S = SDL_LoadBMP("./Boss2.bmp");
		bullet = SDL_LoadBMP("./bullet.bmp");
		SDL_SetColorKey(charset, true, 0x000000);

		if (!window) {
			printf("SDL Window Intitialize Error: %s\n", SDL_GetError());
			isRunning = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		}

		if (!renderer) {
			printf("SDL Renderer Intitialize Error: %s\n", SDL_GetError());
			isRunning = false;
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}

		if (renderer && window) isRunning = true;

		this->liczbaPrzeciwnikow = liczbaprzeciwnikow;
		this->startowaLiczbaPrzeciwnikow = liczbaprzeciwnikow;
		this->level = level;

	}

}

bool Game::handleEvents(Player* p, SDL_Rect* camera, Bullet* bullet, static int* currentTimeEvent) {

	int currentTime = SDL_GetTicks();

	const Uint8* state = SDL_GetKeyboardState(NULL);

	SDL_PumpEvents();

	if (state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D]) p->moveRight(camera);
	if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) p->moveLeft(camera);
	if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) p->moveUp(camera);
	if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) p->moveDown(camera);
	if (state[SDL_SCANCODE_ESCAPE]) isRunning = false;
	if (state[SDL_SCANCODE_N]) return 1;
	if (state[SDL_SCANCODE_SPACE]) {
		if (currentTime - *currentTimeEvent >= 300) {
			*currentTimeEvent = SDL_GetTicks();
			p->addBullet(bullet);
		}
	}


	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		switch (event.type) {

		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}

	}

	return 0;

}

void Game::handleEventsMenu(static int* currentTimeEvent3, Game* game, Enemy* enemies, Player* player, Timing* timer, Bullet* bullet, SDL_Rect* camera, int menustart, Health* health, Boss1* boss1, Boss2* boss2) {

	int currentTime = SDL_GetTicks();

	if (currentTime - *currentTimeEvent3 >= 100 && (SDL_GetTicks() - menustart > 700)) {
		
		const Uint8* state = SDL_GetKeyboardState(NULL);

		SDL_PumpEvents();
		if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
			
			if (select == 4) select = 1;
			else {
				select++;
			}
		}
		if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
			
			if (select == 1) select = 4;
			else {
				select--;
			}

		}
		if (state[SDL_SCANCODE_ESCAPE]) {
			isMenu = 0; 
			isRunning = false;
		}

		if (state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE]) {
			if (select == 1 || select == 2 || select == 3) {
				isMenu = 0;
				playerHit = 0;
				score = 0;
				multiplier = 1;
				game->changeLevel(select);

				for (int i = 0; i < MAX_ENEMIES; i++) {
					enemies[i].Reset();
					enemies[i].changeSpace(BASIC_ENEMY_SPEED_B + static_cast<int>(game->getLevel()*ENEMY_SPEED_BONUS_PER_ROUND_B));
				}

				for (int i = 0; i < MAX_HEALTH_PACKETS; i++) {
					health[i].Reset();
				}

				for (int i = 0; i < game->getHowManyBosses1(); i++) {
					boss1[i].Reset();
				}
				game->howManyBosses1 = game->getLevel() % 2 ? game->getLevel() / 2 + 1 : 0;

				for (int i = 0; i < game->getHowManyBosses2(); i++) {
					boss2[i].Reset();
				}
				game->howManyBosses2 = game->getLevel() % 2 ?  0 : 1;
				

				player->reset(bullet, 0);
				timer->reset();
				*camera = {0,0, SCREEN_WIDTH, ((SCREEN_HEIGHT * 6) / 7) };

				game->changeStartNumberOfEnemies(BASIC_NUMBER_OF_ENEMIES + ((game->getLevel()-1) * BONUS_ENEMIES_PER_ROUND));
				game->changeNumberOfEnemies(BASIC_NUMBER_OF_ENEMIES + ((game->getLevel() - 1) * BONUS_ENEMIES_PER_ROUND));

				long int frameStart = 0;
				int timeOfFrame = 0;
				int timeStrzal = -1;
			}
			else if (select == 4) {
				isMenu = 0; 
				isRunning = false;
			}
		}
		

		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			switch (event.type) {

			case SDL_QUIT:
				isMenu = 0;
				isRunning = false;
				break;
			default:
				break;
			}

		}

		*currentTimeEvent3 = SDL_GetTicks();

	}

	
}
	

void Game::update(char* text, int posX, int posY, SDL_Rect* camera, Enemy* enemies, int number_of_enemies, Player* p, Bullet* Bullet, static int* currentTimeEvent, Health* Health, Boss1* boss1, static int* boss1hit, Boss2* boss2, static int* boss2hit){

	int currentTime = SDL_GetTicks();

	if (currentTime - *currentTimeEvent >= INVIS_TIME) {
		isInvis = 0;
	}
	
	background = SDL_LoadBMP("./background.bmp");
	clearScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	for (int i = 0; i < howManyBosses2; i++) {
		if (boss2[i].getHP()>0) {
				
			for (int k = 10; k <= 210; k += 20) {
					DrawSurface(background, bullet, boss2[i].getPosX() + k, boss2[i].getPosY() + boss2[i].getExtraY());
					if (checkCollision(SDL_Rect{ posX, posY, PLAYER_SIZE, PLAYER_SIZE }, SDL_Rect{ (int)boss2[i].getPosX() + k, (int)(boss2[i].getPosY() + boss2[i].getExtraY()), BULLET_SIZE, BULLET_SIZE })) {
						if (p->getHP() > 0) if (currentTime - *currentTimeEvent >= INVIS_TIME) {
							*currentTimeEvent = SDL_GetTicks(); p->changeHP(p->getHP() - 1); printf("WHOA!"); 
							isInvis = 1; multiplier = 1; playerHit++; if (p->getHP() == 0) { isGameover = 1; p->changeHP(MAX_HEALTH); }
						}
					}
			}
			
			for (int k = 350; k <= 550; k += 20) {
					DrawSurface(background, bullet, boss2[i].getPosX() + k, boss2[i].getPosY() + boss2[i].getExtraY());
					if (checkCollision(SDL_Rect{ posX, posY, PLAYER_SIZE, PLAYER_SIZE }, SDL_Rect{ (int)boss2[i].getPosX() + k, (int)(boss2[i].getPosY() + boss2[i].getExtraY()), BULLET_SIZE, BULLET_SIZE })) {
						if (p->getHP() > 0) if (currentTime - *currentTimeEvent >= INVIS_TIME) {
							*currentTimeEvent = SDL_GetTicks(); p->changeHP(p->getHP() - 1); printf("WHOA!"); 
							isInvis = 1; multiplier = 1; playerHit++; if (p->getHP() == 0) { isGameover = 1; p->changeHP(MAX_HEALTH); }
						}
					}
			}
					
			DrawSurface(background, Boss2_S, boss2[i].getPosX() + boss2[i].getExtraX(), boss2[i].getPosY());
			for (int j = 0; j < MAX_BULLETS; j++) {
				if (Bullet[j].Exists() == 1) {
					if (checkCollision(SDL_Rect{ Bullet[j].CurrentPosX(), Bullet[j].CurrentPosY(), BULLET_SIZE, BULLET_SIZE }, SDL_Rect{ (int)boss2[i].getPosX() + boss2[i].getExtraX(), (int)boss2[i].getPosY(), PLAYER_SIZE, PLAYER_SIZE })) {

						if (currentTime - *boss2hit >= 500) {
							boss2[i].changeHP(boss2[i].getHP() - 1);
							if (boss2[i].getHP() == 0) {
								score += multiplier * 5;
								multiplier++;
							}
							*boss2hit = SDL_GetTicks();
						}

					}
				}
			}
								
		}
	}
		
	for (int i = 0; i < howManyBosses1; i++) {
		if (boss1[i].getHP() > 0) {
			DrawSurface(background, Boss1_S, boss1[i].getPosX(), boss1[i].getPosY());
			for (int j = 0; j < boss1[i].getLiczbaPociskowMax(); j++) {

				float x = boss1[i].getPosX() + boss1[i].getRadius() * sin(M_PI * 2 * (boss1[i].getAngle(j)) / 360);
				float y = boss1[i].getPosY() + boss1[i].getRadius() * cos(M_PI * 2 * (boss1[i].getAngle(j)) / 360);
				DrawSurface(background, bullet, x, y);



				if (checkCollision(SDL_Rect{ posX, posY, PLAYER_SIZE, PLAYER_SIZE }, SDL_Rect{ (int)x, (int)y, BULLET_SIZE, BULLET_SIZE})){
					if (p->getHP() > 0) if (currentTime - *currentTimeEvent >= INVIS_TIME) {
						*currentTimeEvent = SDL_GetTicks(); p->changeHP(p->getHP() - 1); printf("WHOA!"); isInvis = 1; multiplier = 1; playerHit++; if (p->getHP() == 0) { isGameover = 1; p->changeHP(MAX_HEALTH); }
					}
				}

			}
		}

	}

	for (int i = 0; i < MAX_HEALTH_PACKETS; i++) {
		if (Health[i].getExists()) {
			DrawSurface(background, health, Health[i].getPosX(), Health[i].getPosY());
			if (checkCollision(SDL_Rect{Health[i].getPosX(), Health[i].getPosY(), BULLET_SIZE, BULLET_SIZE }, SDL_Rect{ posX, posY, PLAYER_SIZE, PLAYER_SIZE }) && p->getHP()< MAX_HEALTH) {
				Health[i].changeExists(0);
				p->changeHP(p->getHP() + 1);
			}
		}	
	}
	for (int i = 0; i < number_of_enemies; i++) {
		if (!(enemies[i].getCzyTrafiony())) {
			DrawSurface(background, enemy_S, enemies[i].getPosX(), enemies[i].getPosY());

			int extraX = enemies[i].getFirstBulletX();
			int extraY = enemies[i].getFirstBulletY();
			int x1 = enemies[i].getPosX() + extraX;
			DrawSurface(background, bullet, x1, enemies[i].getPosY());
			int x2 = enemies[i].getPosX() - extraX;
			DrawSurface(background, bullet, x2, enemies[i].getPosY());
			int y1 = enemies[i].getPosY() + extraY;
			DrawSurface(background, bullet, enemies[i].getPosX(), y1);
			int y2 = enemies[i].getPosY() - extraY;
			DrawSurface(background, bullet, enemies[i].getPosX(), y2);

			if (checkCollision(SDL_Rect{x1, enemies[i].getPosY(), BULLET_SIZE, BULLET_SIZE }, SDL_Rect{ posX, posY, PLAYER_SIZE, PLAYER_SIZE })) {
				 if (p->getHP() > 0) if (currentTime - *currentTimeEvent >= INVIS_TIME) {
					 *currentTimeEvent = SDL_GetTicks(); p->changeHP(p->getHP() - 1); printf("WHOA!"); isInvis = 1; multiplier = 1; playerHit++; if (p->getHP() == 0) { isGameover = 1; p->changeHP(MAX_HEALTH); }
				}
			}
			if (checkCollision(SDL_Rect{x2, enemies[i].getPosY(), BULLET_SIZE, BULLET_SIZE }, SDL_Rect{ posX, posY, PLAYER_SIZE, PLAYER_SIZE })) {
				 if (p->getHP() > 0) if (currentTime - *currentTimeEvent >= INVIS_TIME) {
					*currentTimeEvent = SDL_GetTicks(); p->changeHP(p->getHP() - 1); printf("WHOA!"); isInvis = 1; multiplier = 1; playerHit++; if (p->getHP() == 0) { isGameover = 1; p->changeHP(MAX_HEALTH); }
				}
			}
			if (checkCollision(SDL_Rect{enemies[i].getPosX(), y1, BULLET_SIZE, BULLET_SIZE }, SDL_Rect{ posX, posY, PLAYER_SIZE, PLAYER_SIZE })) {
				 if (p->getHP() > 0) if (currentTime - *currentTimeEvent >= INVIS_TIME) {
					 *currentTimeEvent = SDL_GetTicks(); p->changeHP(p->getHP() - 1); printf("WHOA!"); isInvis = 1; multiplier = 1; playerHit++; if (p->getHP() == 0) { isGameover = 1; p->changeHP(MAX_HEALTH); }
				}
			}
			if (checkCollision(SDL_Rect{enemies[i].getPosX(), y2, BULLET_SIZE, BULLET_SIZE }, SDL_Rect{ posX, posY, PLAYER_SIZE, PLAYER_SIZE })) {
				 if (p->getHP() > 0) if (currentTime - *currentTimeEvent >= INVIS_TIME) {
					 *currentTimeEvent = SDL_GetTicks(); p->changeHP(p->getHP() - 1); printf("WHOA!"); isInvis = 1; multiplier = 1; playerHit++; if (p->getHP() == 0) { isGameover = 1; p->changeHP(MAX_HEALTH); }
				}
			}
		}
		
	}
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (Bullet[i].Exists() == 1) {
			DrawSurface(background, bullet, Bullet[i].CurrentPosX(), Bullet[i].CurrentPosY());
			for (int j = 0; j < number_of_enemies; j++) {
				if (checkCollision(SDL_Rect{ Bullet[i].CurrentPosX(), Bullet[i].CurrentPosY(), BULLET_SIZE, BULLET_SIZE}, SDL_Rect{enemies[j].getPosX(), enemies[j].getPosY(), PLAYER_SIZE, PLAYER_SIZE })) {
					if (!(enemies[j].getCzyTrafiony())) {
						printf("TRAFIENIE!");
						score += multiplier;
						multiplier++;
						this->changeNumberOfEnemies(this->getNumberOfEnemies() - 1);
						enemies[j].trafiony();
					}
					
				}
			}

			for (int j = 0; j < howManyBosses1; j++) {

				if (boss1[j].getHP() > 0) {

					if (checkCollision(SDL_Rect{ Bullet[i].CurrentPosX(), Bullet[i].CurrentPosY(), BULLET_SIZE, BULLET_SIZE }, SDL_Rect{ (int)boss1[j].getPosX(), (int)boss1[j].getPosY(), PLAYER_SIZE, PLAYER_SIZE })) {
						
						if (currentTime - *boss1hit >= 500) {
							boss1[j].changeHP(boss1[j].getHP() - 1);
							if (boss1[j].getHP() == 0) {
								score += multiplier * 5;
								multiplier++;
							}
							*boss1hit = SDL_GetTicks();
						}
						
					}
				}

			}

		}
		
	}
	SDL_BlitSurface(background, camera, screen, NULL);
	DrawSurface(screen, eti, SCREEN_WIDTH / 2, (SCREEN_HEIGHT - (SCREEN_HEIGHT / 7)) / 2);
	clearInfo(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	
}

void Game::zeros(char* tab, int a, int b, bool nulls) {
	for (int i = a; i < b; i++) {
		tab[i] = nulls ? '\0' : '0';
	}
}

void Game::convertToChar(char* tab, int num, int start) {
	while (num > 0) {
		tab[start] = ((num % 10) + '0');
		start--;
		num /= 10;
	}
}

void Game::AddString(char* target, char* add, int begin, int end) {
	for (int i = begin; i < end; i++) {
		target[i] = add[i - begin];
	}
}

void Game::updateTimer(Timing* timer, Player* p, Boss1* boss1, Boss2* boss2) {

	char number[11];
	char number2[4];
	char number3[5];
	char number4[3];
	char number5[4];
	char number6[4];
	char number7[3];
	char number8[5];

	int time2 = timer->getCurrentTime();
	int enemies = this->getNumberOfEnemies();
	int enemieshit = this->getStartNumberOfEnemies() - this->getNumberOfEnemies();
	int playerhit = this->getPlayerhit();
	int hp = p->getHP();
	int level = this->getLevel();
	int Multiplier = multiplier;
	int Score = score;
	int accuracy = 0;

	if (score == 0) {
		accuracy = 0;
	}

	else {
		accuracy = static_cast<int>((((float)score - ((float)playerhit * 10.0)) / (float)score) * 100);
		if (accuracy < 0) accuracy = 0;
	}

	if (accuracy >= 95) grade = SDL_LoadBMP("./SS.bmp");
	else if(accuracy < 95 && accuracy >= 90) grade = SDL_LoadBMP("./S.bmp");
	else if (accuracy < 90 && accuracy >= 80) grade = SDL_LoadBMP("./A.bmp");
	else if (accuracy < 80 && accuracy >= 60) grade = SDL_LoadBMP("./B.bmp");
	else if (accuracy < 60 && accuracy >= 40) grade = SDL_LoadBMP("./C.bmp");
	else if (accuracy < 40 && accuracy >= 0) grade = SDL_LoadBMP("./D.bmp");

	DrawSurface(info, grade, 600, 30);
	
	number[10] = '\0';
	number2[3] = '\0';
	number3[4] = '\0';
	number4[2] = '\0';
	number5[3] = '\0';
	number6[3] = '\0';
	number7[2] = '\0';
	number8[4] = '\0';

	zeros(number, 0, 10);
	zeros(number2, 0, 3);
	zeros(number6, 0, 4);
	zeros(number8, 0, 4);
	zeros(number3, 0, 5);
	zeros(number4, 0, 2);
	zeros(number7, 0, 2);
	zeros(number5, 0, 3);

	convertToChar(number, time2, 9);
	convertToChar(number2, enemies, 2);
	convertToChar(number3, enemieshit, 3);
	convertToChar(number4, hp, 1);
	convertToChar(number5, playerhit, 2);
	convertToChar(number6, level, 2);
	convertToChar(number7, Multiplier, 1);
	convertToChar(number8, Score, 3);
	
	char fulltext[100];
	zeros(fulltext, 0, 100, 1);
	char fulltext2[100];
	zeros(fulltext2, 0, 100, 1);

	char time[7] = { "Time: " };
	char enemiess[11] = { " RED ETI: " };
	char hit[8] = { " (Hit: " };
	char health[6] = { " HP: " };
	char hit2[14] = { "       (Hit: " };

	AddString(fulltext, time, 0, 6);
	AddString(fulltext, number, 6, 16);
	AddString(fulltext, enemiess, 16, 26);
	AddString(fulltext, number2, 26, 29);
	AddString(fulltext, hit, 29, 36);
	AddString(fulltext, number3, 36, 40);

	fulltext[40] = ')';

	AddString(fulltext, health, 41, 46);
	AddString(fulltext, hit2, 46, 59);
	AddString(fulltext, number5, 59, 62);

	fulltext[62] = ')';


	char levell[8] = { "Level: " };
	char mult[14] = { " Multiplier: " };
	char sc[9] = { " Score: " };
	char acc[12] = { " Accuracy: " };

	AddString(fulltext2, levell, 0, 7);
	AddString(fulltext2, number6, 7, 10);
	AddString(fulltext2, mult, 10, 23);
	AddString(fulltext2, number7, 23, 25);
	AddString(fulltext2, sc, 25, 33);
	AddString(fulltext2, number8, 33, 37);
	AddString(fulltext2, acc, 37, 48);
	
	if (accuracy == 100) {
		fulltext2[48] = '1';
		fulltext2[49] = '0';
		fulltext2[50] = '0';
		fulltext2[51] = '%';
	}
	else {
		fulltext2[48] = (accuracy / 10) % 10 + '0';
		fulltext2[49] = accuracy % 10 + '0';
		fulltext2[50] = '%';
	}
	
	bool b = 0;

	if (howManyBosses2 != 1) {
		char assasin[] = { " Assasin(s): " };
		AddString(fulltext2, assasin, 51, 64);
		b = 1;
	}
	else {
		char bombardier[] = { " Bombardier: " };
		AddString(fulltext2, bombardier, 51, 64);
	}
	int sum = 0;
	if (b == 1) {
		for (int i = 0; i < howManyBosses1; i++) {
			sum += boss1[i].getHP();
		}
		
	}
	else {
		sum = boss2[0].getHP();
	}

	SDL_Rect r;
	r.x = 520;
	r.y = 28;
	r.w = b ? 50.0 * ( (float)sum/float(howManyBosses1 * BOSS1_HP) ) : 50 * ((float)sum / float(howManyBosses2 * BOSS2_HP));
	r.h = 10;

	SDL_FillRect(info, &r, SDL_MapRGB(info->format, 0, 255, 0));
	
	DrawString(this->getInfo(), 10, 10, fulltext,
		this->getCharset(), 100);
	DrawString(this->getInfo(), 10, 30, fulltext2,
		this->getCharset(), 100);
 }

 int Game::getHowManyBosses1()
 {
	 return howManyBosses1;
 }

 int Game::getHowManyBosses2()
 {
	 return howManyBosses2;
 }

 void Game::changeHowManyBosses1(int n)
 {
	 howManyBosses1 = n;
 }

 void Game::changeHowManyBosses2(int n)
 {
	 howManyBosses2 = n;
 }

void Game::render(Player* player) {

	SDL_Rect r;
	r.x = 375;
	r.y = 8;
	r.w = 10 * player->getHP();
	r.h = 10;

	SDL_FillRect(info, &r, SDL_MapRGB(info->format, 0, 255, 0));

	if (isInvis == 1) {
		SDL_SetSurfaceColorMod(screen, 255, 129, 129);
	}
	
	SDL_Texture* textureInfo = SDL_CreateTextureFromSurface(renderer, info);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, screen);

	SDL_RenderClear(renderer);

	SDL_Rect topLeftViewport;
	topLeftViewport.x = 0;
	topLeftViewport.y = 0;
	topLeftViewport.w = SCREEN_WIDTH;
	topLeftViewport.h = SCREEN_HEIGHT / 7;
	SDL_RenderSetViewport(renderer, &topLeftViewport);

	SDL_RenderCopy(renderer, textureInfo, NULL, NULL);

	SDL_Rect LeftViewport;
	LeftViewport.x = 0;
	LeftViewport.y = SCREEN_HEIGHT / 7;
	LeftViewport.w = SCREEN_WIDTH;
	LeftViewport.h = (SCREEN_HEIGHT - (SCREEN_HEIGHT / 7));
	SDL_RenderSetViewport(renderer, &LeftViewport);

	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_RenderPresent(renderer);

	SDL_FreeSurface(screen);
	screen = NULL;
	SDL_FreeSurface(info);
	info = NULL;
	SDL_FreeSurface(background);
	background = NULL;
	SDL_FreeSurface(grade);

	SDL_DestroyTexture(texture);
	texture = NULL;
	SDL_DestroyTexture(textureInfo);
	textureInfo = NULL;

}

void Game::renderMenu(){

	menu = SDL_LoadBMP("./menu.bmp");

	int tab[4] = { 175, 225, 275, 335 };

	SDL_Rect r;
	r.x = 200;
	r.y = tab[select - 1];
	r.w = 10;
	r.h = 10;

	SDL_FillRect(menu, &r, SDL_MapRGB(menu->format, 0, 255, 0));

	SDL_Texture* textureMenu = SDL_CreateTextureFromSurface(renderer, menu);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textureMenu, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_FreeSurface(menu);
	SDL_DestroyTexture(textureMenu);

}

void Game::renderGameover(){

	gameover = SDL_LoadBMP("./gameover.bmp");

	int tab[2] = {185, 275};

	SDL_Rect r;
	r.x = 200;
	r.y = tab[select - 1];
	r.w = 10;
	r.h = 10;

	SDL_FillRect(gameover, &r, SDL_MapRGB(gameover->format, 0, 255, 0));

	SDL_Texture* texturegameOver = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texturegameOver, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_FreeSurface(gameover);
	SDL_DestroyTexture(texturegameOver);

}

void Game::handleEventsGameover(int* currentTimeEvent3, Game* game, Enemy* enemies, Player* player, Timing* timer, Bullet* bullet, SDL_Rect* camera, int gameoverstart, Health* health, Boss1* boss1, Boss2* boss2){

	int currentTime = SDL_GetTicks();

	if ((currentTime - *currentTimeEvent3 >= 100) && (SDL_GetTicks() - gameoverstart > GAME_OVER_DELAY)) {

		const Uint8* state = SDL_GetKeyboardState(NULL);

		SDL_PumpEvents();
		if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {

			if (select == 2) select = 1;
			else {
				select++;
			}
		}
		if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {

			if (select == 1) select = 2;
			else {
				select--;
			}

		}
		if (state[SDL_SCANCODE_ESCAPE]) {
			isGameover = 0; isRunning = false;
		}

		if (state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE]) {
			if (select == 1) {
				isGameover = 0;
				playerHit = 0;
				multiplier = 1;
				score = 0;
				game->changeLevel(1);

				for (int i = 0; i < MAX_ENEMIES; i++) {
					enemies[i].Reset();
					enemies[i].changeSpace(BASIC_ENEMY_SPEED_B + static_cast<int>(game->getLevel()*ENEMY_SPEED_BONUS_PER_ROUND_B));
				}

				for (int i = 0; i < MAX_HEALTH_PACKETS; i++) {
					health[i].Reset();
				}

				for (int i = 0; i < game->getHowManyBosses1(); i++) {
					boss1[i].Reset();
				}
				game->howManyBosses1 = game->getLevel() % 2 ? game->getLevel() / 2 + 1 : 0;

				for (int i = 0; i < game->getHowManyBosses2(); i++) {
					boss2[i].Reset();
				}
				game->howManyBosses2 = game->getLevel() % 2 ? 0 : 1;

				player->reset(bullet, 0);
				timer->reset();
				*camera = { 0,0, SCREEN_WIDTH, ((SCREEN_HEIGHT * 6) / 7) };

				game->changeStartNumberOfEnemies(BASIC_NUMBER_OF_ENEMIES + ((game->getLevel() - 1) * BONUS_ENEMIES_PER_ROUND));
				game->changeNumberOfEnemies(BASIC_NUMBER_OF_ENEMIES + ((game->getLevel() - 1) * BONUS_ENEMIES_PER_ROUND));

				long int frameStart = 0;
				int timeOfFrame = 0;
				int timeStrzal = -1;
			}
			else if (select == 2) {
				isGameover = 0; 
				isMenu = 1;
			}
		}


		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			switch (event.type) {

			case SDL_QUIT:
				isMenu = 0;
				isRunning = false;
				break;
			default:
				break;
			}

		}

		*currentTimeEvent3 = SDL_GetTicks();

	}
}


void Game::closeGame(bool b) {
	if (screen != NULL && info != NULL && background != NULL) {
		SDL_FreeSurface(screen);
		SDL_FreeSurface(info);
		SDL_FreeSurface(background);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(eti);
		SDL_FreeSurface(enemy_S);
		SDL_FreeSurface(bullet);
	}

	SDL_RenderClear(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	if (b) {
		SDL_Quit();
	}
	
}

SDL_Surface* Game::getScreen(){
	return screen;
}
SDL_Surface* Game::getInfo() {
	return info;
}

SDL_Surface* Game::getCharset(){
	return charset;
}

void Game::changeNumberOfEnemies(int n){
	liczbaPrzeciwnikow = n;
}

int Game::getNumberOfEnemies(){
	return liczbaPrzeciwnikow;
}

int Game::getStartNumberOfEnemies(){
	return startowaLiczbaPrzeciwnikow;
}

int Game::getLevel(){
	return level;
}

int Game::getPlayerhit(){
	return playerHit;
}

void Game::changePlayerhit(int n){
	playerHit = n;
}

bool Game::getIsMenu(){
	return isMenu;
}

bool Game::getIsGameover(){
	return isGameover;
}

int Game::getSelect(){
	return select;
}

bool Game::getIsInvis(){
	return isInvis;
}

int Game::getMultiplier(){
	return multiplier;
}

int Game::getScore(){
	return score;
}

void Game::changeMultiplier(int n){
	multiplier = n;
}

void Game::changeScore(int n){
	score = n;
}

void Game::changeSelect(int n){
	select = n;
}

void Game::changeIsMenu(bool b){
	isMenu = b;
}

void Game::changeLevel(int n){
	level = n;
}

void Game::changeIsGameover(bool b){
	isGameover = b;
}

void Game::changeIsInvis(bool b){
	isInvis = b;
}

void Game::changeStartNumberOfEnemies(int n){
	startowaLiczbaPrzeciwnikow = n;
}

void Game::clearScreen(int width, int height){
	screen = SDL_CreateRGBSurface(0, width, (height - (height / 7)), 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

void Game::clearInfo(int width, int height) {
	info = SDL_CreateRGBSurface(0, width, (height / 7), 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

bool Game::running() {
	return isRunning;
}

bool Game::checkCollision(SDL_Rect first, SDL_Rect second){

	int topF;
	int topS;
	int leftF;
	int	leftS;
	int bottomF;
	int	bottomS;
	int rightF;
	int	rightS;

	int flag = 1;

	leftF = first.x;
	rightF = first.x + first.w;
	topF = first.y;
	bottomF = first.y + first.h;

	leftS = second.x;
	rightS = second.x + second.w;
	topS = second.y;
	bottomS = second.y + second.h;

	if (leftF >= rightS){
		flag = 0;
	}
	if (bottomF <= topS){
		flag = 0;
	}
	if (rightF <= leftS){
		flag = 0;
	}
	if (topF >= bottomS){
		flag = 0;
	}

	return flag;
}
