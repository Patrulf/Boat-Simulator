#include "WaterCollider.h"

WaterCollider::WaterCollider(float p_x, float p_z, int p_width,int p_height) :
	xPos(p_x),
	zPos(p_z),
	width(p_width),
	height(p_height)
{
	xMinBound = xPos - width / 2;
	xMaxBound = xPos + (width / 2);
	zMinBound = zPos - height / 2;
	zMaxBound = zPos + (height / 2);
}


WaterCollider::~WaterCollider()
{
}

void WaterCollider::SetCollisionPoints(std::vector<float> p_points)
{
	collisionPoints = p_points;
}



std::vector<float> WaterCollider::GetCollisionPoints()
{
	return collisionPoints;
}

float WaterCollider::GetXMaxBounds()
{
	return xMaxBound;
}

float WaterCollider::GetZMaxBounds()
{
	return zMaxBound;
}

float WaterCollider::GetXMinBounds()
{
	return xMinBound;
}

float WaterCollider::getZMinBounds()
{
	return zMinBound;
}
