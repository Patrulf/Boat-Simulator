#include "TNTManager.h"
#include "TNT.h"
#include <algorithm>
#include "Randomizer.h"
#include "Timer.h"
#include "CollisionManager.h"
#include <functional>
#include "Ship.h"
#include "LevelManager.h"
#include "ServiceLocator.h"
#include "ShaderManager.h"
#include "Water.h"
#include "WaterCollider.h"

TNTManager::TNTManager(int p_tntAmount, int p_maxWidth, int p_maxHeight, Ship* p_player) : tntAmount{ p_tntAmount },
width{ p_maxWidth }, height{ p_maxHeight }
{
	shaderManager = ServiceLocator<ShaderManager>::GetService();

	player = p_player;
	TNTTimer = new Timer(0.5f);
	basicProgramID = shaderManager->GetBasicShader();
	levelManager = ServiceLocator<LevelManager>::GetService();
	water = ServiceLocator<Water>::GetService();
}

TNTManager::~TNTManager()
{
	for (int i = 0; i < static_cast<unsigned int>(tnts.size()); i++)
	{
		delete tnts[i];
	}
	tnts.erase(std::remove(tnts.begin(), tnts.end(), nullptr), tnts.end());

	delete TNTTimer;
	TNTTimer = nullptr;
}

void TNTManager::SetMatrix(mat4 p_myMatrix)
{
	myMatrix = p_myMatrix;
}

void TNTManager::Update(float p_delta)
{
	if (TNTTimer->Tick(p_delta))
	{
		CreateTNT();
	}
	for (int i = 0; i < static_cast<unsigned int>(tnts.size()); i++)
	{
		tnts[i]->SetMatrix(myMatrix);
		tnts[i]->Update(p_delta);
	}
}


void TNTManager::Draw()
{
	for (int i = 0; i < static_cast<unsigned int>(tnts.size()); i++)
	{
		tnts[i]->Draw();
	}
}


std::vector<TNT*> TNTManager::GetTNTs()
{
	return tnts;
}

void TNTManager::Collision(CircleCollider* p_colliderToCollideWith)
{
	for (auto& it : tnts)
	{
		if (CollisionManager::IsColliding(it->GetCircleCollider(), p_colliderToCollideWith))
		{
			levelManager->GoToScene("LoseState");
		}
	}

}


void TNTManager::DestroyTNT(TNT* p_tnt)
{
	for (int i = 0; i < static_cast<unsigned int>(tnts.size()); i++)
	{
		if (tnts[i] == p_tnt)
		{
			delete tnts[i];
			tnts[i] = nullptr;
			break;
		}
	}
	tnts.erase(std::remove(tnts.begin(), tnts.end(), nullptr), tnts.end() );
}


void TNTManager::CreateTNT()
{
	if (static_cast<unsigned int>(tnts.size()) < tntAmount)
	{
		float distanceToPlayerSquared = 10.0f;

		float xMin = water->GetWaterCollider()->GetXMinBounds();
		float xMax = water->GetWaterCollider()->GetXMaxBounds();
		float zMin = water->GetWaterCollider()->getZMinBounds();
		float zMax = water->GetWaterCollider()->GetZMaxBounds();

		float x = static_cast<float>(Random(xMin, xMax));
		float z = static_cast<float>(Random(zMin, zMax));
		while (std::pow(player->GetPosition().x - x, 2) + std::pow(player->GetPosition().z - z, 2) < distanceToPlayerSquared)
		{
			x = static_cast<float>(Random(xMin, xMax));
			z = static_cast<float>(Random(zMax, zMax));
		}
		TNT* tnt = new TNT(x, -0.5f, z, basicProgramID);
		tnt->SetDestructionCallback(std::bind(&TNTManager::DestroyTNT,this,std::placeholders::_1));
		tnts.push_back(tnt);
	}
}