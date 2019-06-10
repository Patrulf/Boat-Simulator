#pragma once
#include <string>
#include "5SD805_math.h"
#include "5SD805_helper.h"
#include <functional>
#include <vector>

class Plane;

class Button
{
public:
	Button(GLuint& p_programID,const char* p_textureFilepath, vec3 p_position,std::function<void()> p_onClickCallback);
	~Button();
	void Draw();
	void SetMatrix(mat4 p_myMatrix);
	void OnClick();
	vec3 GetPosition();
private:

	std::vector<float> vertices;
	std::vector<GLushort> indices;
	std::function<void()> onClickCallback;

	vec3 position;
	Plane* plane;

	GLuint texture;
	GLuint programID;
	GLuint vao;
	GLuint indexBufferID;
	GLuint vertexBufferID;

	mat4 modelMatrix;
	mat4 myMatrix;
};

