#pragma once
#include "glew.h"
#include "glfw3.h"

class Window
{
public:
	Window(GLint p_width, GLint p_height);
	~Window();
	GLFWwindow* GetWindow();
private:
	GLFWwindow* window;
};

