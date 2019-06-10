/*
Code of the basics of how to get glew and glfw started taken from video tutorials found below.
https://www.youtube.com/watch?annotation_id=annotation_3716210897&feature=iv&index=2&list=PLRtjMdoYXLf6zUMDJVRZYV-6g6n62vet8&src_vid=vGptI11wRxE&v=mGC4T9AG4nc
*/

#include <iostream>
#define GLEW_STATIC
#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
#define BufferOffset(bytes) ((char *)NULL + (bytes))

#include "5SD805_helper.h"
#include "StateMachine.h"
#include "IState.h"
#include "GameState.h"
#include "Window.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "MainMenu.h"
#include "LevelManager.h"
#include "GameRunner.h"
#include "ShaderManager.h"

const GLint _WIDTH = 800, _HEIGHT = 600;


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	Window window(_WIDTH,_HEIGHT);

	GLint _screenWidth, _screenHeight;
	glfwGetFramebufferSize(window.GetWindow(),&_screenWidth, &_screenHeight);

	if (window.GetWindow() == nullptr)
	{
		std::cout << "Failed to create window" << '\n';
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window.GetWindow());
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << '\n';
		return EXIT_FAILURE;
	}

	glViewport(0, 0, _screenWidth, _screenHeight);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	GameRunner* gameRunner = new GameRunner();
	gameRunner->SetIsRunning(true);
	ServiceLocator<GameRunner>::SetService(gameRunner);
	
	ShaderManager* shaderManager = new ShaderManager();
	LevelManager* levelManager = new LevelManager();
	InputManager* inputManager = new InputManager(window);
	ServiceLocator<ShaderManager>::SetService(shaderManager);
	ServiceLocator<InputManager>::SetService(inputManager);
	ServiceLocator<LevelManager>::SetService(levelManager);

	levelManager->InitStates();
	
	double deltaTime = 0.0f;
	double lastFrameTime = 0.0f;
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		if (!gameRunner->GetIsRunning())
			glfwSetWindowShouldClose(window.GetWindow(), GLFW_TRUE);

		double totalTime = glfwGetTime();
		deltaTime = totalTime - lastFrameTime;
		lastFrameTime = glfwGetTime();

		levelManager->Update(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		levelManager->Draw();

		glfwPollEvents();
		glfwSwapBuffers(window.GetWindow());
	}
	delete shaderManager;
	shaderManager = nullptr;
	delete gameRunner;
	gameRunner = nullptr;
	delete levelManager;
	levelManager = nullptr;
	delete inputManager;
	inputManager = nullptr;

	glfwTerminate();

	return EXIT_SUCCESS;
}
