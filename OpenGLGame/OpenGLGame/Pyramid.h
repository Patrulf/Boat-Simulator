#pragma once
#include "5SD805_helper.h"
#include <vector>

class Pyramid
{
public:
	Pyramid(int p_width, int p_height);
	~Pyramid();
	void GenerateVerticesAndIndices(float r = 0.f, float g = 0.f, float b = 0.f);

	std::vector<float> GetVertices();
	std::vector<GLushort> GetIndices();
	std::vector<float> GetGroundVertices();

private:
	int width;
	int height;
	std::vector<float> vertices;
	std::vector<GLushort> indices;
	std::vector<float> groundVertices;

	float x;
	float y;
	float z;
};