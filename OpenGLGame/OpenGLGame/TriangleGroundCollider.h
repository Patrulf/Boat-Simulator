#pragma once
#include "GroundCollider.h"
class TriangleGroundCollider :
	public GroundCollider
{
public:
	TriangleGroundCollider(float p_x, float p_z);
	~TriangleGroundCollider();
	void SetCollisionPoints(std::vector<float>);
	std::vector<float> GetCollisionPoints();
private:
	std::vector <float> collisionPoints;
	float xPos;
	float zPos;
	int width;
	int height;
	float xMinBound;
	float xMaxBound;
	float zMinBound;
	float zMaxBound;
};

