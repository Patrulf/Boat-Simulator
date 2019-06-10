#pragma once
class GameRunner
{
public:
	GameRunner();
	~GameRunner();
	bool GetIsRunning();
	void SetIsRunning(bool p_state);	
private:
	bool isRunning;
};

