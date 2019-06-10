#include "TriangleGroundCollider.h"



TriangleGroundCollider::TriangleGroundCollider(float p_x, float p_z)	
{
	xPos = p_x;
	zPos = p_z;
}


TriangleGroundCollider::~TriangleGroundCollider()
{
}

void TriangleGroundCollider::SetCollisionPoints(std::vector<float> p_points)
{
	collisionPoints = p_points;
}

std::vector<float> TriangleGroundCollider::GetCollisionPoints()
{
	return collisionPoints;
}
