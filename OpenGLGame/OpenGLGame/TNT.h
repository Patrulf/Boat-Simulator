#pragma once
#include "5SD805_helper.h"
#include <vector>
#include <functional>

class CircleCollider;
class Sphere;

class TNT
{
public:
	TNT(float p_x, float p_y, float p_z, GLuint p_programID);
	~TNT();

	void Update(float p_delta);
	void Draw();
	void SetMatrix(mat4 p_myMatrix);

	CircleCollider* GetCircleCollider();
	void SetDestructionCallback(std::function<void(TNT*)> p_callback);

private:
	std::function<void(TNT*)> destructionCallback;
	void Destruction();
	float rot;
	float scale_;

	std::vector<float> vertices;
	std::vector<GLushort> indices;

	mat4 modelMatrix;
	GLuint programID;
	GLuint vao;
	GLuint indexBufferID;
	GLuint vertexBufferID;
	mat4 myMatrix;
	vec3 position;

	Sphere* sphere;
	CircleCollider* circleCollider;
};

