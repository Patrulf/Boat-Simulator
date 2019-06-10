#pragma once
#include "5SD805_math.h"
#include "5SD805_helper.h"
#include <vector>

class Plane;
class Box;

class ButtonSelector
{
public:
	ButtonSelector(vec3 p_position, GLuint& p_programID);
	~ButtonSelector();

	void Draw();
	void SetMatrix(mat4 p_myMatrix);
	void SetPosition(vec3 p_position);

private:
	Plane* plane;
	Box* box;
	vec3 position;

	std::vector<float> vertices;
	std::vector<GLushort> indices;

	GLuint programID;
	GLuint vao;
	GLuint indexBufferID;
	GLuint vertexBufferID;

	mat4 modelMatrix;
	mat4 myMatrix;
};

