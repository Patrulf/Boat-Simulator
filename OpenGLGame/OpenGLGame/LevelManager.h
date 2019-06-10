#pragma once
#include <string>


/*Based on statemachine by Jerry Jonsson from the Augustus engine.*/
class StateMachine;

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void Update(float p_delta);
	void Draw();

	void InitStates();
	void GoToScene(std::string p_sceneID);
private:
	void UpdateCurrentScene();
	StateMachine* stateManager;
	std::string nextSceneID;
};

