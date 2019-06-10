#pragma once


class Timer
{
public:
	Timer(float p_time);
	~Timer();
	bool Tick(float p_delta);
private:
	float timeLimit;
	float currentTime;
};

