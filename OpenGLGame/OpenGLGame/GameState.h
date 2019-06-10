#pragma once

#include "IState.h"


class camera;
class Water;
class Ship;
class InputManager;
class CollisionManager;
class CargoManager;
class TNTManager;
class ShaderManager;

class GameState : public IState
{
public:
	CargoManager* cargoManager;
	camera* myCam;
	Water* myWater;
	Ship* myShip;
	InputManager* inputManager;
	CollisionManager* collisionManager;
	TNTManager* tntManager;
	ShaderManager* shaderManager;

	void Enter();
	void Exit();

	void Update(float p_delta);
	void Draw();
	GameState();
	~GameState();
};

