#ifndef Enemy_h
#define Enemy_h

class Enemy {

public:
	Enemy();
	~Enemy();
	int getBulletCounter();
	int getFirstBulletX();
	int getFirstBulletY();
	int getSpace();
	int getPosX();
	int getPosY();
	int getCzyTrafiony();
	void changeSpace(int n);
	void trafiony();
	void resetBulletCounter();
	void Reset();
	void fire();

private:
	int posX;
	int posY;
	int space;
	int firstBulletX;
	int firstBulletY;
	int bulletCounter;
	int czyTrafiony;
};



#endif 