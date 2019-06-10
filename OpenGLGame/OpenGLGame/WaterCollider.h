#pragma once
#include "GroundCollider.h"
class WaterCollider :
	public GroundCollider
{
public:
	WaterCollider(float p_x, float p_z, int p_width, int p_height);
	~WaterCollider();
	void SetCollisionPoints(std::vector<float>);
	std::vector<float> GetCollisionPoints();
	float GetXMaxBounds();
	float GetZMaxBounds();
	float GetXMinBounds();
	float getZMinBounds();
private:
	float xPos;
	float zPos;
	int width;
	int height;
	float xMinBound;
	float xMaxBound;
	float zMinBound;
	float zMaxBound;

	std::vector <float> collisionPoints;
};

