#pragma once
#include "5SD805_helper.h"
#include <vector>
class Sphere
{
public:
	Sphere(float p_r);
	~Sphere();
	void GenerateVerticesAndIndices(float r, float g, float b);
	std::vector<float> GetVertices();
	std::vector<GLushort> GetIndices();
	float GetRadius();
private:
	float x;
	float y;
	float z;
	float radius;

	std::vector<float> vertices;
	std::vector<GLushort> indices;
};

