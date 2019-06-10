#include "CargoManager.h"
#include "Cargo.h"
#include <algorithm>
#include "Randomizer.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "ServiceLocator.h"
#include "LevelManager.h"
#include "Ship.h"
#include "ShaderManager.h"
#include "Water.h"
#include "WaterCollider.h"

CargoManager::CargoManager(int p_coinAmount, int p_maxWidth, int p_maxHeight, Ship* p_player) : cargoAmount{p_coinAmount},
width{ p_maxWidth }, height{p_maxHeight}
{
	water = ServiceLocator<Water>::GetService();
	shaderManager = ServiceLocator<ShaderManager>::GetService();

	cargoTimer = new Timer(5.0f);
	basicProgramID = shaderManager->GetBasicShader();
	levelManager = ServiceLocator<LevelManager>::GetService();
	player = p_player;
}

CargoManager::~CargoManager()
{
	for (int i = 0; i < static_cast<unsigned int>(cargos.size()); i++)
	{
		delete cargos[i];
	}
	cargos.clear();
	delete cargoTimer;
	cargoTimer = nullptr;
}

void CargoManager::SetMatrix(mat4 p_myMatrix)
{
	myMatrix = p_myMatrix;
}
void CargoManager::Update(float p_delta)
{
	if (cargoTimer->Tick(p_delta))
	{
		CreateCoin();
	}

	for (int i = 0; i < cargos.size(); i++)
	{
		cargos[i]->SetMatrix(myMatrix);
		cargos[i]->Update(p_delta);
	}
}

void CargoManager::Draw()
{
	for (int i = 0; i < static_cast<unsigned int>(cargos.size()); i++)
	{
		cargos[i]->Draw();
	}
}

std::vector<Cargo*> CargoManager::GetCoins()
{
	return cargos;
}

void CargoManager::Collision(CircleCollider* p_colliderToCollideWith)
{
	for (auto& it : cargos)
	{
		if (CollisionManager::IsColliding(it->GetCircleCollider(), p_colliderToCollideWith))
		{
			levelManager->GoToScene("WinState");
		}
	}
}

void CargoManager::CreateCoin()
{
	if (static_cast<unsigned int>(cargos.size()) < cargoAmount)
	{
		float distanceToPlayerSquared = 5.0f;

		float xMin = water->GetWaterCollider()->GetXMinBounds();
		float xMax = water->GetWaterCollider()->GetXMaxBounds();
		float zMin = water->GetWaterCollider()->getZMinBounds();
		float zMax = water->GetWaterCollider()->GetZMaxBounds();

		float x = static_cast<float>(Random(xMin, xMax));
		float z = static_cast<float>(Random(zMin, zMax));
		while (std::pow(player->GetPosition().x - x, 2) + std::pow(player->GetPosition().z - z, 2) < distanceToPlayerSquared)
		{
			x = static_cast<float>(Random(xMin, xMax));
			z = static_cast<float>(Random(zMin, zMax));
		}
		Cargo* cargo = new Cargo(x, -0.5f, z, basicProgramID);
		cargos.push_back(cargo);
	}
} 