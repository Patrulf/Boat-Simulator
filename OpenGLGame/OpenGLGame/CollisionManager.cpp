#include "CollisionManager.h"
#include "TriangleGroundCollider.h"
#include "WaterCollider.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

vec3 CollisionManager::GetNormal(CircleCollider* p_circleCollider, WaterCollider* p_waterCollider)
{
	vec3 normal = { 0,0,0 };
	if (p_circleCollider->GetX() > p_waterCollider->GetXMaxBounds())
	{
		normal = { -1,0,0 };
	}
	if (p_circleCollider->GetX() < p_waterCollider->GetXMinBounds())
	{
		normal = { 1,0,0 };
	}

	if (p_circleCollider->GetZ() > p_waterCollider->GetZMaxBounds())
	{
		normal = { 0,0,-1 };
	}
	if (p_circleCollider->GetZ() < p_waterCollider->getZMinBounds())
	{
		normal = { 0,0,1 };
	}

	return normal;

}

bool CollisionManager::IsOnWater(CircleCollider* p_circleCollider, WaterCollider* p_waterCollider)
{
	if (p_circleCollider->GetX() < p_waterCollider->GetXMaxBounds()
		&& p_circleCollider->GetX() > p_waterCollider->GetXMinBounds()
		&& p_circleCollider->GetZ() > p_waterCollider->getZMinBounds()
		&& p_circleCollider->GetZ() < p_waterCollider->GetZMaxBounds()
		)
	{
		return true;
	}
	return false;
}

bool CollisionManager::IsColliding(CircleCollider* p_colliderOne, CircleCollider* p_colliderTwo)
{
	float distanceBetweenCenterpoints = (p_colliderOne->GetX() - p_colliderTwo->GetX())*(p_colliderOne->GetX() - p_colliderTwo->GetX())
		+ (p_colliderOne->GetZ() - p_colliderTwo->GetZ())*(p_colliderOne->GetZ() - p_colliderTwo->GetZ());
	
	float radiusSumSquared = (p_colliderOne->GetRadius() + p_colliderTwo->GetRadius())*(p_colliderOne->GetRadius() + p_colliderTwo->GetRadius());
	
	if (distanceBetweenCenterpoints <= radiusSumSquared)
	{
		return true;
	}
	return false;
}