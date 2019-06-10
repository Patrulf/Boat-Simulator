#pragma once
#include "IState.h"
#include "ServiceLocator.h"

class camera;
class MenuScreen;
class ShaderManager;

class WinState : public IState
{
public:
	WinState();
	~WinState();
	void Enter();
	void Exit();
	void Draw();
	void Update(float p_delta);
private:
	ShaderManager* shaderManager;
	camera* myCam;
	MenuScreen* menuScreen;
};

