#ifndef Timing_h
#define Timing_h

#include <stdio.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

class Timing {

public:
	Timing();
	~Timing();

	void reset();
	int getCurrentTime();
	char* convertTimeToString(int time);

private:
	float currentTime;
	float startingTime;
	int timeInSeconds;
};






#endif 