#include "LevelManager.h"
#include "StateMachine.h"
#include "GameState.h"
#include "MainMenu.h"
#include <cassert>
#include "ServiceLocator.h"
#include "LoseState.h"
#include "WinState.h"

LevelManager::LevelManager()
{
	stateManager = new StateMachine();
	nextSceneID = "";
}

void LevelManager::InitStates()
{
	assert( ServiceLocator<LevelManager>::GetService() != nullptr );
	stateManager->AddState("GameState", new GameState());
	stateManager->AddState("MenuState", new MainMenu());
	stateManager->AddState("LoseState", new LoseState());
	stateManager->AddState("WinState", new WinState());
	stateManager->SetState("MenuState");
}

LevelManager::~LevelManager()
{
	delete stateManager;
	stateManager = nullptr;
}

void LevelManager::Update(float p_delta)
{
	stateManager->Update(p_delta);
	UpdateCurrentScene();
}

void LevelManager::UpdateCurrentScene()
{
	if (nextSceneID != "")
	{
		stateManager->SetState(nextSceneID);
		nextSceneID = "";
	}
}

void LevelManager::GoToScene(std::string p_sceneID)
{
	nextSceneID = p_sceneID;
}

void LevelManager::Draw()
{
	stateManager->Draw();
}
