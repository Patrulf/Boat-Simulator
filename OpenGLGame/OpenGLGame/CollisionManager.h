#pragma once
#include "CircleCollider.h"
#include "5SD805_math.h"

class WaterCollider;
class TriangleGroundCollider;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	static bool IsOnWater(CircleCollider* p_triangleCollider, WaterCollider* p_waterCollider);
	static vec3 GetNormal(CircleCollider* p_triangleCollider, WaterCollider* p_waterCollider);
	static bool IsColliding(CircleCollider* p_colliderOne, CircleCollider* p_colliderTwo);
private:
	float xPos;
	float zPos;
	int width;
	int height;
};

