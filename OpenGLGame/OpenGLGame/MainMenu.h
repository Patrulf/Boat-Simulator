#pragma once
#include "IState.h"

class camera;
class MenuScreen;
class ShaderManager;

class MainMenu : public IState
{
public:
	MainMenu();
	~MainMenu();
	void Update(float p_delta);
	void Draw();
	void Enter();
	void Exit();

private:
	ShaderManager* shaderManager;
	camera* myCam;
	MenuScreen* menuScreen;
};

