#include "GameRunner.h"



GameRunner::GameRunner() : 
	isRunning(false)
{
}


GameRunner::~GameRunner()
{
}

bool GameRunner::GetIsRunning()
{
	return isRunning;
}

void GameRunner::SetIsRunning(bool p_state)
{
	isRunning = p_state;
}