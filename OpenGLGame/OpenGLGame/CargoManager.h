#pragma once
#include <vector>
#include "5SD805_helper.h"

class Cargo;
class Timer;
class CircleCollider;
class LevelManager;
class Ship;
class ShaderManager;
class Water;

class CargoManager
{
private:
	std::vector<Cargo*> cargos;
	int cargoAmount;
	int width;
	int height;
	Timer* cargoTimer;
	void CreateCoin();
	GLuint basicProgramID;
	mat4 myMatrix;
	LevelManager* levelManager;
	Ship* player;
	ShaderManager* shaderManager;
	Water* water;
public:

	void SetMatrix(mat4 p_matrix);
	void Update(float p_delta);
	void Draw();
	std::vector<Cargo*> GetCoins();
	void Collision(CircleCollider* p_colliderToCollideWith);

	CargoManager(int p_coinAmount, int p_maxWidth, int p_maxHeight, Ship* p_player);
	~CargoManager();


};

