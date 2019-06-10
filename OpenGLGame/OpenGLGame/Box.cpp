#include "Box.h"



Box::Box()
{
}


Box::~Box()
{

}

std::vector<float> Box::GetVertices()
{
	return vertices;
}

std::vector<GLushort> Box::GetIndices()
{
	return indices;
}


//only works for trianglestrips.
void Box::GenerateVerticesAndIndices(float r, float g, float b)
{
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);

	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);

	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);

	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);

	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);

	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);

	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);

	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(6);
	indices.push_back(2);
	indices.push_back(4);

	indices.push_back(3);
	indices.push_back(5);

	indices.push_back(1);
	indices.push_back(7);

	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(5);

	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(5);
	indices.push_back(7);

	indices.push_back(7);

	indices.push_back(6);
	indices.push_back(0);
	indices.push_back(7);
	indices.push_back(1);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
}