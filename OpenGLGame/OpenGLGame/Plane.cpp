#include "Plane.h"
#include <cmath>
#include <stdio.h>




Plane::Plane(int p_rows, int p_columns)
{
	rows = p_rows;
	columns = p_columns;
}

Plane::~Plane()
{
}



std::vector<float> Plane::GetVertices() {
	return vertices;
}
std::vector<GLushort> Plane::GetIndices() {
	return indices;
}

std::vector<float> Plane::GetUvs() {
	return uvs;
}

std::vector<float> Plane::GetGroundCollider()
{
	return groundCollider;
}

void Plane::GenerateVerticesAndIndices(float r, float g, float b) {

	vertices.clear(); 

	{
		float xPos = 0 - rows / 2;
		float zPos = 0 - columns / 2;
		if (rows % 2 == 0)
		{
			xPos = 0.5f - rows / 2;
		}
		if (columns % 2 == 0)
		{
			zPos = 0.5f - columns / 2;
		}
		float yPos = 0;
		for (int y = 0; y < columns; y++)
		{
			for (int x = 0; x < rows; x++)
			{
				vertices.push_back(xPos);
				vertices.push_back(yPos);
				vertices.push_back(zPos);

				xPos++;
			}
			xPos = 0 - rows / 2;
			if (rows % 2 == 0)
			{
				xPos = 0.5f - rows / 2;
			}
			zPos++;

		}
	}


	for (int y = 0; y < columns; y++)
	{
		for (int x = 0; x < rows; x++)
		{
			{
				vertices.push_back(r);
				vertices.push_back(g);
				vertices.push_back(b);

			}			
		}
	}

//https://stackoverflow.com/questions/5915753/generate-a-plane-with-triangle-strips
	indices.clear();
	int degenerateCounter = 0;
	for (int y = 0; y < columns -1; y++) {

		for (int x = 0; x < rows; x++) {
			indices.push_back((y * rows + x));
			indices.push_back(((y + 1) * rows + x));
			degenerateCounter++;
			if (degenerateCounter % rows == 0 && y < columns-2)
			{
				indices.push_back( rows + ((y+1)*rows) -1 );
				indices.push_back(rows + ((y)*rows));
			}
		}
	}

	for (int i = 0; i < vertices.size() / 2; i++)
	{
		groundCollider.push_back(vertices[i]);
	}

}

void Plane::GenerateVerticesIndicesAndUVs()
{

	vertices.clear();
	{
		float xPos = 0 - rows / 2;
		float zPos = 0 - columns / 2;
		if (rows % 2 == 0)
		{
			xPos = 0.5f - rows / 2;
		}
		if (columns % 2 == 0)
		{
			zPos = 0.5f - columns / 2;
		}
		float yPos = 0;
		for (int y = 0; y < columns; y++)
		{
			for (int x = 0; x < rows; x++)
			{
				vertices.push_back(xPos);
				vertices.push_back(yPos);
				vertices.push_back(zPos);
				xPos++;
			}
			xPos = 0 - rows / 2;
			if (rows % 2 == 0)
			{
				xPos = 0.5f - rows / 2;
			}
			zPos++;

		}
	}

	for (int y = 0; y < columns; y++)
	{
		for (int x = 0; x < rows; x++)
		{
			{
				vertices.push_back(1);
				vertices.push_back(1);
				vertices.push_back(1);
			}
		}
	}

	{
		//https://stackoverflow.com/questions/5915753/generate-a-plane-with-triangle-strips
		indices.clear();
		int degenerateCounter = 0;
		for (int y = 0; y < columns - 1; y++) {

			for (int x = 0; x < rows; x++) {
				indices.push_back((y * rows + x));
				indices.push_back(((y + 1) * rows + x));
				degenerateCounter++;
				if (degenerateCounter % rows == 0 && y < columns - 2)
				{
					indices.push_back(rows + ((y + 1)*rows) - 1);
					indices.push_back(rows + ((y)*rows));
				}
			}
		}
	}

	for (int i = 0; i < vertices.size() / 2; i++)
	{
		groundCollider.push_back(vertices[i]);
	}


	{
		float xPos = 0;
		float yPos = 0;
		for (int y = 0; y < columns; y++)
		{
			for (int x = 0; x < rows; x++)
			{
				if (xPos != 0)
					vertices.push_back(xPos / (rows-1) );
				else
					vertices.push_back(0);
				if (yPos != 0)
					vertices.push_back(yPos / (columns-1));
				else
					vertices.push_back(0);
				xPos++;
			}
			xPos = 0;
			yPos++;
		}
	}
}


void Plane::Update(float p_delta, float p_deltaMouseX, float p_deltaMouseY)
{
}

void Plane::SetMatrix(mat4 p_myMatrix)
{
	m_myMatrix = p_myMatrix;
}

