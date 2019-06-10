#include "Pyramid.h"
#include <cmath>
#include <stdio.h>


Pyramid::Pyramid(int p_width, int p_height)
{
	width = 40;
	height = 40;
}


Pyramid::~Pyramid()
{
}

std::vector<float> Pyramid::GetGroundVertices() {
	return groundVertices;

}

std::vector<float> Pyramid::GetVertices() {
	return vertices;
}
std::vector<GLushort> Pyramid::GetIndices() {
	return indices;
}


void Pyramid::GenerateVerticesAndIndices(float r, float g, float b) {

	float positionX = 0;
	float positionY = 0+0.5;
	float positionZ = 0+0.5;
	vertices.push_back(positionX);
	vertices.push_back(positionY);
	vertices.push_back(positionZ);

	positionX = 0;
	positionY = 0 - 0.5;
	positionZ = 0 - 0.5;
	vertices.push_back(positionX);
	vertices.push_back(positionY);
	vertices.push_back(positionZ);


	positionX = 0 + 0.5;
	positionY = 0 + 0.5;
	positionZ = 0 - 0.5;
	vertices.push_back(positionX);
	vertices.push_back(positionY);
	vertices.push_back(positionZ);

	positionX = 0 - 0.5;
	positionY = 0 + 0.5;
	positionZ = 0 - 0.5;
	vertices.push_back(positionX);
	vertices.push_back(positionY);
	vertices.push_back(positionZ);



	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);


	vertices.push_back(1);
	vertices.push_back(0);
	vertices.push_back(0);

	vertices.push_back(0);
	vertices.push_back(1);
	vertices.push_back(0);

	vertices.push_back(0);
	vertices.push_back(0);
	vertices.push_back(1);

	vertices.push_back(1);
	vertices.push_back(1);
	vertices.push_back(1);

	groundVertices.push_back(vertices[0]);
	groundVertices.push_back(vertices[1]);
	groundVertices.push_back(vertices[2]);

	groundVertices.push_back(vertices[6]);
	groundVertices.push_back(vertices[7]);
	groundVertices.push_back(vertices[8]);

	groundVertices.push_back(vertices[9]);
	groundVertices.push_back(vertices[10]);
	groundVertices.push_back(vertices[11]);

}
