#ifndef Health_h
#define Health_h

class Health {

public:
	Health();
	~Health();
	int getPosX();
	int getPosY();
	int getExists();
	void changeExists(int n);
	void Reset();


private:
	int exists;
	int posX;
	int posY;

};




#endif 