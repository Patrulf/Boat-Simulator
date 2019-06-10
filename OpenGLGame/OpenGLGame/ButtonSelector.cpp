#include "ButtonSelector.h"
#include "Plane.h"
#include "Box.h"


ButtonSelector::ButtonSelector(vec3 p_position, GLuint& p_programID)
{
	position = { p_position.x,p_position.y,p_position.z};

	plane = new Plane(2, 2);
	plane->GenerateVerticesAndIndices(1,1,0);
	vertices = plane->GetVertices();
	indices = plane->GetIndices();

	mat4 translationMatrix = translation(position.x, position.y, position.z);
	
	mat4 rotationMatrix = rotation(90 * PI / 180, 1.0f, 0.0f, 0.0f);
	mat4 secondRotationMatrix = rotation(180 * PI / 180, 0.0f, 1.0f, 0.0f);
	mat4 scaleMatrix = scale(1.0f);
	modelMatrix = translationMatrix * rotationMatrix * secondRotationMatrix * scaleMatrix;

	programID = p_programID;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &indexBufferID);
	glGenBuffers(1, &vertexBufferID);
}


ButtonSelector::~ButtonSelector()
{
	delete plane;
	plane = nullptr;
	glDeleteBuffers(1, &indexBufferID);
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vao);
}

void ButtonSelector::SetPosition(vec3 p_position)
{
	position = { p_position.x,p_position.y,p_position.z };

	mat4 translationMatrix = translation(position.x, position.y, position.z);

	mat4 rotationMatrix = rotation(90 * PI / 180, 1.0f, 0.0f, 0.0f);
	mat4 secondRotationMatrix = rotation(180 * PI / 180, 0.0f, 1.0f, 0.0f);
	mat4 scaleMatrix = scale(1.0f);
	modelMatrix = translationMatrix * rotationMatrix * secondRotationMatrix * scaleMatrix;
}

void ButtonSelector::SetMatrix(mat4 p_myMatrix)
{
	myMatrix = p_myMatrix;
}

void ButtonSelector::Draw()
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
