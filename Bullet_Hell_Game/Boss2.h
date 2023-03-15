#ifndef Boss2_h
#define Boss2_h
#define LICZBA_POCISKOW_MAX 12
class Boss2 {

public:
	Boss2();
	~Boss2();
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
	int newPosY;
	int newPosX;
	bool strona;
	int extraX;
	int extraY;
	int space;
	float angle[LICZBA_POCISKOW_MAX + 1];
	float Radius;
	int bulletCounter;
	int HP;
	int liczbaPociskowMax;
};



#endif 