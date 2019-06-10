#pragma once
#include "5SD805_helper.h"
#include <vector>

class Plane
{
public:
	Plane(int p_rows, int p_columns); 
	~Plane();
	void Update(float p_delta, float p_deltaMouseX, float p_deltaMouseY);
	

	void SetMatrix(mat4 p_myMatrix);
	void GenerateVerticesAndIndices(float r = 0.f, float g = 0.f, float b = 0.f);

	void GenerateVerticesIndicesAndUVs();

	std::vector<float> GetVertices();
	std::vector<GLushort> GetIndices();
	std::vector<float> GetUvs();

	std::vector<float> GetGroundCollider();

private:
	int rows; //width
	int columns; //height
	std::vector<float> vertices;
	std::vector<GLushort> indices;
	std::vector<float> uvs;
	std::vector<float> groundCollider;


	mat4 m_myMatrix;
};

