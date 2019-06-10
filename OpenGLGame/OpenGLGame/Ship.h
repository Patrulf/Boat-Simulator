#pragma once
#include "5SD805_helper.h"
#include <vector>

class Pyramid;
class InputManager;
class TriangleGroundCollider;
class PerlinNoise;
class CircleCollider;

class Ship
{
public:
	Ship(float p_x, float p_y, float p_z, GLuint p_programID);
	~Ship();

	void DrawShip();
	void SetMatrix(mat4 p_myMatrix);
	vec3 GetForwardVector();
	vec3 GetPosition();
	void SetPosition(vec3 p_position);
	void Update(float p_delta);
	CircleCollider* GetCircleCollider();
	vec3 GetMovementVector();
	float GetSpeed();
private:

	float speed;
	float time = 0.0f;
	PerlinNoise* noise;
	TriangleGroundCollider* groundCollider;
	void Input(float p_delta);
	InputManager* inputManager;
	Pyramid* pyramid;
	mat4 modelMatrix;
	vec3 position;
	vec3 movementVector;
	vec3 forwardVector;
	float turnRate;

	std::vector<float> vertices;
	std::vector<GLushort> indices;

	CircleCollider* circleCollider;

	GLuint programID;
	GLuint vao;
	GLuint indexBufferID;
	GLuint vertexBufferID;
	mat4 m_myMatrix;
};

