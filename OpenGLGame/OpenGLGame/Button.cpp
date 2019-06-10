#include "Button.h"
#include "Plane.h"
#include "SOIL2/SOIL2/SOIL2.h"

Button::Button(GLuint& p_programID, const char* p_textureFilepath, vec3 p_position, std::function<void()> p_onClickCallback) {

	onClickCallback = p_onClickCallback;
	position = { p_position.x,p_position.y,p_position.z };
	plane = new Plane(4, 2);
	plane->GenerateVerticesIndicesAndUVs();

	vertices = plane->GetVertices();
	indices = plane->GetIndices();

	mat4 translationMatrix = translation(position.x, position.y, position.z+0.1f);
	mat4 rotationMatrix = rotation(90 * PI / 180, 1.0f, 0.0f, 0.0f);
	mat4 secondRotationMatrix = rotation(180 * PI / 180, 0.0f, 1.0f, 0.0f);
	mat4 scaleMatrix = scale(1.0f);
	modelMatrix = translationMatrix * rotationMatrix * secondRotationMatrix * scaleMatrix;

	programID = p_programID;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &indexBufferID);
	glGenBuffers(1, &vertexBufferID);

	//Wrapping parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//filtering parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int imageWidth, imageHeight;
	unsigned char* image = SOIL_load_image(p_textureFilepath, &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Button::~Button() {
	glDeleteBuffers(1, &indexBufferID);
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vao);

	delete plane;
	plane = nullptr;
}

void Button::OnClick()
{
	onClickCallback();
}

void Button::Draw() {

	glBindTexture(GL_TEXTURE_2D, texture);
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
	glVertexAttribPointer(C, 3, GL_FLOAT, GL_FALSE, 0, (char *)NULL + ((vertices.size() * sizeof(vertices[0])) / 8) * 3);

	glEnableVertexAttribArray(C);
	/////////////////////////////////////////////////////////////////////////////////////
	GLint K = glGetAttribLocation(programID, "uvs");
	glVertexAttribPointer(K, 2, GL_FLOAT, GL_FALSE, 0, BufferOffset(0) + ((vertices.size() * sizeof(vertices[0])) / 8) * 6);
	
	glEnableVertexAttribArray(K);
	////////////////////////////////////////////////////////////////////////////////////////

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
	glDisableVertexAttribArray(K);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Button::SetMatrix(mat4 p_myMatrix) {
	myMatrix = p_myMatrix;
}

vec3 Button::GetPosition() {
	return position;
}
