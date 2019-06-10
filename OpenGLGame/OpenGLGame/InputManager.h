#pragma once
#include "glew.h"
#include "glfw3.h"
#include <vector>
#include <tuple>
class Window;

enum keyState
{
	PRESSED,
	HOLD,
	RELEASED,
};

struct Key {
	int key;
	keyState state;
};

class InputManager
{
public:
	InputManager(Window& p_window);
	~InputManager();
	bool RegisterKeyInput(int p_scancode);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool FindKey(int p_key);
	bool IsKeyDown(int p_key);
	bool IsKeyDownOnce(int p_key);
private:
	std::vector<Key> keys;

	Window& window;
};

