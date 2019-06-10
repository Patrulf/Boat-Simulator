#include "Cargo.h"
#include "Pyramid.h"
#include "CircleCollider.h"
#include "Box.h"


//rename to cargo i guess.
Cargo::Cargo(float p_x, float p_y, float p_z, GLuint p_programID)
{
	rot = 0.0f;
	position = { p_x,p_y,p_z };

	mat4 translationMatrix = translation(p_x, p_y, p_z);
	mat4 rotationMatrix = rotation(0.0f, 0.0f, 1.0f, 0.0f);
	mat4 scaleMatrix = scale(1.0f);
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	box = new Box();
	box->GenerateVerticesAndIndices(1,1,1);
	
	vertices = box->GetVertices();
	indices = box->GetIndices();
	programID = p_programID;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &indexBufferID);
	glGenBuffers(1, &vertexBufferID);
	circleCollider = new CircleCollider(position.x, position.z, 1.0f);
}

Cargo::~Cargo()
{
	delete box;
	box = nullptr;
	delete circleCollider;
	circleCollider = nullptr;

	glDeleteBuffers(1, &indexBufferID);
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vao);
}

void Cargo::Update(float p_delta)
{
	rot += p_delta;
	mat4 translationMatrix = translation(position.x, position.y, position.z);
	mat4 rotationMatrix = rotation(rot, 0.0f, 1.0f, 0.0f);
	circleCollider->SetPosition(position.x, position.z);
}

CircleCollider* Cargo::GetCircleCollider()
{
	return circleCollider;
}

void Cargo::Draw()
{
	glUseProgram(programID);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

	GLint P = glGetAttribLocation(programID, "vPositions");
	glVertexAttribPointer(P, 3, GL_FLOAT, GL_FALSE, 0, BufferOffset(0));
	glEnableVertexAttribArray(P);

	//////////////////////////////////////////////////////////////////////////////
	GLint C = glGetAttribLocation(programID, "colors");
	glVertexAttribPointer(C, 3, GL_FLOAT, GL_FALSE, 0, (char *)NULL + ((vertices.size() * sizeof(vertices[0])) / 2));
	glEnableVertexAttribArray(C);
	/////////////////////////////////////////////////////////////////////////////////////

	GLint M = glGetUniformLocation(programID, "myMat");
	if (M != -1)
	{
		glUniformMatrix4fv(M, 1, false, myMatrix.m);
	}

	GLint Model = glGetUniformLocation(programID, "modelMatrix");
	if (Model != -1)
	{
		glUniformMatrix4fv(Model, 1, false, modelMatrix.m);
	}

	////////////////////////////////////////////////////////////

	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, 0);

	// Cleanup
	glDisableVertexAttribArray(P);
	glDisableVertexAttribArray(C);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Cargo::SetMatrix(mat4 p_myMatrix)
{
	myMatrix = p_myMatrix;
}
