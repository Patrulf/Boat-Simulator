#include "Window.h"



Window::Window(GLint p_width, GLint p_height)
{
	window = glfwCreateWindow(p_width, p_height, "Boat Simulator", nullptr, nullptr);
}

GLFWwindow* Window::GetWindow()
{
	return window;
}

Window::~Window()
{
	glfwDestroyWindow(window);
	window = nullptr;
}
