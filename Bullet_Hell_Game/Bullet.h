#ifndef Bullet_h
#define Bullet_h

class Bullet {

	friend class Player;

public:
	Bullet();
	~Bullet();
	int CurrentPosX();
	int CurrentPosY();
	int StartingPosX();
	int StartingPosY();
	int Exists();

private:
	int startingPosX;
	int startingPosY;
	int currentPosX;
	int currentPosY;
	int exists;

};



#endif