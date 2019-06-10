#include "GameState.h"
#include "camera.h"
#include "Plane.h"
#include "Water.h"
#include "Ship.h"
#include "CollisionManager.h"
#include "CargoManager.h"
#include "TNTManager.h"
#include "ServiceLocator.h"
#include "ShaderManager.h"

GameState::GameState()
{
}
GameState::~GameState()
{
}


//create all shaders from main?
void GameState::Enter()
{
	collisionManager = new CollisionManager();
	ServiceLocator<CollisionManager>::SetService(collisionManager);	
	shaderManager = ServiceLocator<ShaderManager>::GetService();

	GLuint waterID = shaderManager->GetWaterShader();
	myWater = new Water(0, 0, 0, waterID);

	GLuint floatingProgramID = shaderManager->GetFloatingShader();
	myShip = new Ship(0, -0.5, 0, floatingProgramID);
	myCam = new camera();

	cargoManager = new CargoManager(1, myWater->GetWidth(), myWater->GetHeight(), myShip);
	tntManager = new TNTManager(5, myWater->GetWidth(), myWater->GetHeight(), myShip);
}

void GameState::Exit()
{
	delete collisionManager;
	collisionManager = nullptr;
	delete myCam;
	myCam = nullptr;
	delete myWater;
	myWater = nullptr;
	delete myShip;
	myShip = nullptr;
	delete cargoManager;
	cargoManager = nullptr;
	delete tntManager;
	tntManager = nullptr;
}

void GameState::Update(float p_delta)
{
	vec3 cameraForward = myShip->GetForwardVector();
	vec3 cameraPos = myShip->GetPosition();
	myCam->SetCameraForward(cameraForward);
	myCam->LookAtTarget(cameraPos.x,cameraPos.y,cameraPos.z);
	mat4 myProjectionMatrix = myCam->GetProjectionMatrix();
	mat4 myViewMatrix = myCam->GetViewMatrix();
	mat4 myMat = myProjectionMatrix * myViewMatrix;

	myWater->Update(p_delta);
	myWater->SetMatrix(myMat);
	myShip->SetMatrix(myMat);
	myShip->Update(p_delta);

	cargoManager->SetMatrix(myMat);
	cargoManager->Update(p_delta);

	tntManager->SetMatrix(myMat);
	tntManager->Update(p_delta);

	if (!CollisionManager::IsOnWater(myShip->GetCircleCollider(), myWater->GetWaterCollider()))
	{
		vec3 normal = CollisionManager::GetNormal(myShip->GetCircleCollider(),myWater->GetWaterCollider() );
		myShip->GetMovementVector();
		vec3 angle = { myShip->GetMovementVector().x* normal.x, 0, myShip->GetMovementVector().z * normal.z };
		vec3 position = { myShip->GetPosition().x + ((normal.x)- angle.x) * myShip->GetSpeed() * p_delta, myShip->GetPosition().y, myShip->GetPosition().z + ((normal.z)-angle.z) * myShip->GetSpeed() * p_delta };
		position = position * 1.0f;
		myShip->SetPosition(position);
	}
	cargoManager->Collision(myShip->GetCircleCollider());
	tntManager->Collision(myShip->GetCircleCollider());
}

void GameState::Draw()
{
	cargoManager->Draw();
	tntManager->Draw();
	myWater->Draw();
	myShip->DrawShip();
}

