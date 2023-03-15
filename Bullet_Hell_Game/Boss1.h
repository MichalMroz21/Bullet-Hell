#ifndef Boss1_h
#define Boss1_h
#define LICZBA_POCISKOW_MAX 12
class Boss1 {

public:
	Boss1();
	~Boss1();
	int getBulletCounter();
	float getRadius();
	float getAngle(int i);
	int getSpace();
	float getPosX();
	float getPosY();
	int getNewPosY();
	int getNewPosX();
	int getExtraX();
	int getExtraY();
	int getHP();
	void changeHP(int n);
	int getLiczbaPociskowMax();
	void changeSpace(int n);
	void resetBulletCounter();
	void Reset();
	void fire();

private:
	float posX;
	float posY;
	int newPosX;
	int newPosY;
	int extraY;
	int extraX;
	bool strona;
	int space;
	float angle[LICZBA_POCISKOW_MAX + 1];
	float Radius;
	int bulletCounter;
	int HP;
	int liczbaPociskowMax;
};



#endif 