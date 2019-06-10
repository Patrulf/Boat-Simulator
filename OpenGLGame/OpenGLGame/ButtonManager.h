#pragma once
#include <vector>
#include "5SD805_math.h"
#include "5SD805_helper.h"
#include <functional>
#include <tuple>

class Button;
class InputManager;
class ButtonSelector;

class ButtonManager
{
public:
	ButtonManager(GLuint& p_selectorProgramID);
	~ButtonManager();
	void CreateButton(GLuint& p_programID, const char* p_textureFilepath, vec3 p_position, std::function<void()> p_onClickCallback);
	void Update(float p_delta);
	void Draw();
	void Cycle(float p_delta);
	void SetButtonMatrices(mat4 p_myMat);
private:
	ButtonSelector* buttonSelector;
	void SelectButton();
	std::vector<Button*> buttons;
	int _selectedButtonIndex;	
	InputManager* inputManager;
	mat4 myMat;
};

