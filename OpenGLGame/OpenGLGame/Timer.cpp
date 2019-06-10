#include "Timer.h"



Timer::Timer(float p_time) : timeLimit{p_time},
currentTime{0} {}


Timer::~Timer()
{
}


bool Timer::Tick(float p_delta) {
	if (currentTime < timeLimit)
	{
		currentTime += p_delta;
		return false;
	}
	currentTime -= timeLimit;
	return true;
}
