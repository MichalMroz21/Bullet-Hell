#include "Timing.h"

#define TIME_STRING_SIZE 11

Timing::Timing(){
	currentTime = 0;
	timeInSeconds = 0;
	startingTime = SDL_GetTicks();
}

Timing::~Timing(){

}

void Timing::reset(){
	startingTime = SDL_GetTicks();
	currentTime = 0;
	timeInSeconds = 0;
}

char* Timing::convertTimeToString(int time) {
	char number[11];
	number[10] = '\0';
	for (int i = 0; i < 10; i++) {
		number[i] = '0';
	}
	int i = 9;
	while (time > 0) {

		number[i] = ((time % 10) + '0');
		i--;
		time /= 10;
	}

	
	return number;
}


int Timing::getCurrentTime(){
	currentTime = SDL_GetTicks() - startingTime;
	timeInSeconds = currentTime * 0.001;
	return timeInSeconds;
}
