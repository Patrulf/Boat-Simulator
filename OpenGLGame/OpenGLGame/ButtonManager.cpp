#include "ButtonManager.h"
#include "Button.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "ButtonSelector.h"

ButtonManager::ButtonManager(GLuint& p_selectorProgramID) {
	vec3 initPos = { 0,0,0 };
	buttonSelector = new ButtonSelector(initPos, p_selectorProgramID);
	inputManager = ServiceLocator<InputManager>::GetService();
	_selectedButtonIndex = false;
}

ButtonManager::~ButtonManager()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
	delete buttonSelector;
	buttonSelector = nullptr;
}

void ButtonManager::CreateButton(GLuint& p_programID, const char* p_textureFilepath, vec3 p_position, std::function<void()> p_onClickCallback)
{
	Button* button = new Button(p_programID, p_textureFilepath, p_position, p_onClickCallback);
	if (buttons.size() == 0)
		buttons.push_back(button);
	else
		buttons.push_back(button);
}

void ButtonManager::Update(float p_delta)
{
	Cycle(p_delta);
	SelectButton();
}

void ButtonManager::Draw() {

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Draw();
	}

	buttonSelector->Draw();
}

void ButtonManager::SelectButton()
{
	if (inputManager->IsKeyDown(GLFW_KEY_ENTER))
	{
		buttons[_selectedButtonIndex]->OnClick();
	}
}

void ButtonManager::Cycle(float p_delta)
{
	if (inputManager->IsKeyDownOnce(GLFW_KEY_S))
	{
		_selectedButtonIndex--;
	}
	if (inputManager->IsKeyDownOnce(GLFW_KEY_W))
	{
		_selectedButtonIndex++;
	}
	if (_selectedButtonIndex >= (int)buttons.size())
	{
		_selectedButtonIndex = 0;
	}
	if (_selectedButtonIndex < 0)
	{
		_selectedButtonIndex = buttons.size() - 1;
	}

	vec3 selectorPos = buttons[_selectedButtonIndex]->GetPosition();
	selectorPos = { selectorPos.x+4.0f,selectorPos.y,selectorPos.z };
	buttonSelector->SetPosition(selectorPos);
}

void ButtonManager::SetButtonMatrices(mat4 p_myMat)
{
	myMat = p_myMat;
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->SetMatrix(p_myMat);
	}
	buttonSelector->SetMatrix(p_myMat);
}

