#include "Sphere.h"
#include "5SD805_helper.h"
#include "5SD805_math.h"

//http://www.songho.ca/opengl/gl_sphere.html
Sphere::Sphere(float p_r)
{
	radius = p_r;
}

Sphere::~Sphere()
{
}

void Sphere::GenerateVerticesAndIndices(float r, float g, float b)
{
	float xPos = 0.0f;
	float yPos = 0.0f;
	float zPos = 0.0f;
	int width = 40;
	int height = 40;
	float radius = 1.0f;
	float radCurrent = 0.0f;

//spherical coordinates.
//sources.
//https://www.youtube.com/watch?v=Q-RUZIboBeE
//https://github.com/Erkaman/cute-deferred-shading/blob/master/src/main.cpp#L573
	float phi = 0.0f;
	for (int y = 0; y < height; y++){
		float phi = (float)y/(PI/height);
		phi = PI*phi;
		for (int x=0; x<width; x++){			
			xPos = cosf((x*PI * 2) / width)*sinf(phi);
			zPos = sinf((x*PI * 2) / width)*sinf(phi);
			vertices.push_back(xPos);
			vertices.push_back(cosf(phi));
			vertices.push_back(zPos);
		}
		radCurrent = 1.0f;
	}


	for (int y = 0; y < height-1; y++)
	{
		for (int x = 0; x < width; x++)
		{			
			indices.push_back(y*width+x);
			indices.push_back(y*width+x+width);
		}
		if (y < height - 1)
		{
			indices.push_back(y*width);
			indices.push_back(y*width+width);
		}
	}

	for (int i = 0; i<height*width + 2*height; i++)
	{
		vertices.push_back(r);
		vertices.push_back(g);
		vertices.push_back(b);
	}
}

float Sphere::GetRadius()
{
	return radius;
}

std::vector<float> Sphere::GetVertices()
{
	return vertices;
}

std::vector<GLushort> Sphere::GetIndices()
{
	return indices;
}


