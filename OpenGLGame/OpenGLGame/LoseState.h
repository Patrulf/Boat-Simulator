#pragma once
#include "IState.h"
#include "ServiceLocator.h"

class camera;
class MenuScreen;
class ShaderManager;

class LoseState : public IState
{
public:
	LoseState();
	~LoseState();

	void Enter();
	void Exit();
	void Draw();
	void Update(float p_delta);
private:
	camera* myCam;
	MenuScreen* menuScreen;
	ShaderManager* shaderManager;
};

