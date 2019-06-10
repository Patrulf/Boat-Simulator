#include "InputManager.h"
#include "Window.h"
#include <algorithm>

InputManager::InputManager(Window& p_window)
	: window(p_window)
{
	glfwSetWindowUserPointer(window.GetWindow(), this);
	glfwSetKeyCallback(window.GetWindow(), KeyCallback);
}

InputManager::~InputManager()
{
	glfwSetWindowUserPointer(window.GetWindow(), nullptr);
}

bool InputManager::RegisterKeyInput(int p_scanCode)
{
	glfwGetKey(window.GetWindow(), p_scanCode);
	return false;
}

bool InputManager::FindKey(int p_key)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i].key == p_key)
		{
			return true;
		}
	}
	return false;
}

bool InputManager::IsKeyDownOnce(int p_key)
{
	bool exists = false;
	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i].key == p_key && keys[i].state == HOLD)
			return false;

		if (keys[i].key == p_key && keys[i].state == PRESSED)
		{
			keys.erase(keys.begin() + i );
			Key newKey = { p_key,HOLD };
			keys.push_back(newKey);
			exists = true;
		}	
	}
	if (exists)
		return true;

	return false;
}

bool InputManager::IsKeyDown(int p_key)
{
	if (FindKey(p_key))
	{
		return true;
	}
	return false;
}

void InputManager::KeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(p_window) );
	std::vector<Key>& keys = inputManager->keys;
	if (p_action == GLFW_PRESS)
	{
		if (!inputManager->FindKey(p_key))
		{
			Key currentKey = { p_key, PRESSED };
			inputManager->keys.push_back(currentKey);
		}
	}
	if (p_action == GLFW_REPEAT)
	{
		if (inputManager->FindKey(p_key))
		{
			Key currentKey = { p_key, HOLD };
			inputManager->keys.push_back(currentKey);
		}
	}
	if (p_action == GLFW_RELEASE)
	{
		for (int i = 0; i < inputManager->keys.size(); i++)
		{
			if (inputManager->keys[i].key == p_key)
			{
				keys.erase(
					std::remove_if(keys.begin(), keys.end(),
					[&](Key const & key) {
					return key.key == p_key;
				}), keys.end());
			}
		}
	}
}
