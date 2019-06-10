#pragma once
#include "5SD805_helper.h"
#include <vector>

class CircleCollider;
class Pyramid;
class Box;

class Cargo
{
public:
	Cargo(float p_x, float p_y, float p_z, GLuint p_programID);
	~Cargo();

	void Update(float p_delta);
	void Draw();
	void SetMatrix(mat4 p_myMatrix);

	CircleCollider* GetCircleCollider();

private:
	float rot;

	std::vector<float> vertices;
	std::vector<GLushort> indices;

	Pyramid* pyramid;
	Box* box;
	mat4 modelMatrix;
	GLuint programID;
	GLuint vao;
	GLuint indexBufferID;
	GLuint vertexBufferID;
	mat4 myMatrix;
	vec3 position;

	CircleCollider* circleCollider;
};

