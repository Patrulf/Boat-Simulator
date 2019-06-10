#include "WinState.h"
#include "camera.h"
#include "MenuScreen.h"
#include "ServiceLocator.h"
#include "ShaderManager.h"


WinState::WinState()
{
}
WinState::~WinState()
{
}

void WinState::Enter() {
	myCam = new camera();
	shaderManager = ServiceLocator<ShaderManager>::GetService();

	GLuint basicProgramID = shaderManager->GetBasicTexturedShader();
	vec3 position = { 0.0f,0.0f,0.0f };
	menuScreen = new MenuScreen(position, basicProgramID, "../Assets/Win.bmp");
}

void WinState::Exit() {
	delete myCam;
	myCam = nullptr;
	delete menuScreen;
	menuScreen = nullptr;
}

void WinState::Update(float p_delta) {
	myCam->Update(0.0f, -0.1f, 10.0f);
	mat4 myProjectionMatrix = myCam->GetProjectionMatrix();
	mat4 myViewMatrix = myCam->GetViewMatrix();
	mat4 myMat = myProjectionMatrix * myViewMatrix;

	menuScreen->Update(p_delta);
	menuScreen->SetMatrix(myMat);
}

void WinState::Draw() {
	menuScreen->Draw(1, 0, 1);
}