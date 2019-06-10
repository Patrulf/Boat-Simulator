#include "MainMenu.h"
#include "camera.h"
#include "MenuScreen.h"
#include "ServiceLocator.h"
#include "ShaderManager.h"

MainMenu::MainMenu()
{
}

void MainMenu::Enter()
{
	shaderManager = ServiceLocator<ShaderManager>::GetService();
	myCam = new camera();
	GLuint basicProgramID = shaderManager->GetBasicTexturedShader();
	vec3 position = { 0.0f,0.0f,0.0f };
	menuScreen = new MenuScreen(position, basicProgramID, "../Assets/TitleScreen.bmp");
}

void MainMenu::Exit()
{
	delete myCam;
	myCam = nullptr;
	delete menuScreen;
	menuScreen = nullptr;
}

MainMenu::~MainMenu()
{
}

void MainMenu::Update(float p_delta)
{
	myCam->Update(0.0f, -0.1f, 10.0f); //Look at plane we've created I guess.
	mat4 myProjectionMatrix = myCam->GetProjectionMatrix();
	mat4 myViewMatrix = myCam->GetViewMatrix();
	mat4 myMat = myProjectionMatrix * myViewMatrix; //also modelmatrix?	
	
	menuScreen->Update(p_delta);
	menuScreen->SetMatrix(myMat);
}

void MainMenu::Draw()
{
	menuScreen->Draw(1, 0, 1);
}
