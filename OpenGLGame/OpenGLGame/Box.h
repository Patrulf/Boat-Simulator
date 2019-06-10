#pragma once
#include "5SD805_helper.h"
#include <vector>

class Box
{
public:
	Box();
	~Box();

	void GenerateVerticesAndIndices(float r = 0.f, float g = 0.f, float b = 0.f);

	std::vector<float> GetVertices();
	std::vector<GLushort> GetIndices();

private:
	int width;
	int height;
	std::vector<float> vertices;
	std::vector<GLushort> indices;
};

