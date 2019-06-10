#pragma once
#include "5SD805_math.h"
#include "5SD805_helper.h"
#include <vector>

class Plane;
class Box;
class ButtonManager;
class LevelManager;
class GameRunner;
class ShaderManager;

class MenuScreen
{
public:
	MenuScreen(vec3 p_position, GLuint p_programID, std::string p_backgroundFilePath);
	~MenuScreen();
	void Update(float p_delta);
	void Draw(float r, float g, float b);
	void SetMatrix(mat4 p_myMatrix);
	void GoToGameState();
	void Quit();

private:
	GLuint basicID;


	ShaderManager* shaderManager;
	GameRunner* gameRunner;
	LevelManager* _levelManager;
	std::vector<float> vertices;
	std::vector<GLushort> indices;

	vec3 position;
	Plane* plane;
	ButtonManager* buttonManager;


	float x;
	float y;

	GLuint texture;

	GLuint programID;
	GLuint vao;
	GLuint indexBufferID;
	GLuint vertexBufferID;
	mat4 modelMatrix;
	mat4 myMatrix;
};

