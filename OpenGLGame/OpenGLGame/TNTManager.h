#pragma once
#include <vector>
#include "5SD805_helper.h"

class TNT;
class Timer;
class CircleCollider;
class Ship;
class LevelManager;
class ShaderManager;
class Water;

class TNTManager
{
private:
	ShaderManager* shaderManager;
	std::vector<TNT*> tnts;
	int tntAmount;
	int width;
	int height;
	Timer* TNTTimer;
	void CreateTNT();
	GLuint basicProgramID;
	mat4 myMatrix;
	Ship* player;
	LevelManager* levelManager;
	Water* water;
public:

	void DestroyTNT(TNT* tnt);
	void SetMatrix(mat4 p_matrix);
	void Update(float p_delta);
	void Draw();
	std::vector<TNT*> GetTNTs();
	void Collision(CircleCollider* p_colliderToCollideWith);//would need to take variable amount of colliders if we where to make it more dynamic.

	TNTManager(int p_coinAmount, int p_maxWidth, int p_maxHeight, Ship* p_player );
	~TNTManager();
};

