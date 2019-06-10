#include "Water.h"
#include <cmath>
#include <stdio.h>
#include "Plane.h"
#include "WaterCollider.h"
#include "ServiceLocator.h"

Water::Water(float p_x, float p_y, float p_z, GLuint& p_programID)
{
	width = 20;
	height = 20;
	ServiceLocator<Water>::SetService(this);
	mat4 translationMatrix = translation(p_x, p_y, p_z);
	mat4 rotationMatrix = rotation(0.0f, 0.0f, 1.0f, 0.0f);
	mat4 scaleMatrix = scale(1.0f);
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	myPlane = new Plane(21,21); //width & height + 1
	myPlane->GenerateVerticesAndIndices(1.0f,1.0f,1.0f);
	vertices = myPlane->GetVertices();
	indices = myPlane->GetIndices();


	programID = p_programID;
	time = 0.0f;
	deltaX = 0.0f;
	deltaY = 0.0f;
	deltaTime = 0.0f;
	x = p_x;
	y = p_y;
	z = p_z;

	groundCollider = new WaterCollider(x, z,width,height); //width and height = 20, 20

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &indexBufferID);
	glGenBuffers(1, &vertexBufferID);

}

Water::~Water()
{
	glDeleteBuffers(1, &indexBufferID);
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vao);
	//glDeleteProgram(programID);

	delete groundCollider;
	groundCollider = nullptr;
	delete myPlane;
	myPlane = nullptr;
}

int Water::GetWidth()
{
	return width;
}

int Water::GetHeight()
{
	return height;
}


WaterCollider* Water::GetWaterCollider()
{
	return groundCollider;
}

//links for perlin noise functionality:http://flafla2.github.io/2014/08/09/perlinnoise.html
void Water::DrawWater(float r, float g, float b) {

	glUseProgram(programID);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);


	// Attribpointer state is stored in VAO
	GLint P = glGetAttribLocation(programID, "vPositions");
	glVertexAttribPointer(P, 3, GL_FLOAT, GL_FALSE, 0, BufferOffset(0));
	glEnableVertexAttribArray(P);

	//////////////////////////////////////////////////////////////////////////////
	GLint C = glGetAttribLocation(programID, "colors");
	glVertexAttribPointer(C, 3, GL_FLOAT, GL_FALSE, 0, (char *)NULL + ((vertices.size() * sizeof(vertices[0])) / 2));
	glEnableVertexAttribArray(C);
	/////////////////////////////////////////////////////////////////////////////////////

	time += deltaTime;
	GLint T = glGetUniformLocation(programID, "time");
	if (T != -1)
	{
		glUniform1f(T, time);
	}


	GLint model = glGetUniformLocation(programID, "modelMatrix");
	if (model != -1)
	{
		glUniformMatrix4fv(model, 1, false, modelMatrix.m);
	}

	GLint M = glGetUniformLocation(programID, "myMat");
	if (M != -1)
	{
		glUniformMatrix4fv(M, 1, false, myMatrix.m);
	}

	////////////////////////////////////////////////////////////
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, 0);

	// Cleanup
	glDisableVertexAttribArray(P);
	glDisableVertexAttribArray(C);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0); 
	//glDeleteProgram(programID);

}


void Water::Update(float p_delta)
{
	deltaTime = p_delta;
}

void Water::Draw()
{
	DrawWater(1.0f, 1.0f, 1.0f);
}

void Water::SetMatrix(mat4 p_myMatrix)
{
	myMatrix = p_myMatrix;
}

