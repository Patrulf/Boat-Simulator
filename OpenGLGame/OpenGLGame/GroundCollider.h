#pragma once
#include <vector>

class GroundCollider
{
public:
	GroundCollider();
	~GroundCollider();
	virtual void SetCollisionPoints(std::vector<float>) = 0;
	virtual std::vector<float> GetCollisionPoints() = 0;
};

