#include "Ship.h"
#include "Pyramid.h"
#include "iostream"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "TriangleGroundCollider.h"
#include "PerlinNoise.h"
#include "CircleCollider.h"


Ship::Ship(float p_x, float p_y, float p_z, GLuint p_programID) :
	speed(5.0f) //<- lol
{
	movementVector = { 0.f,0.f,0.f };
	turnRate = 0.0f;
	position = { p_x,p_y,p_z };
	forwardVector = { 0.0f,0.0f,1.0f };
	mat4 translationMatrix = translation(p_x,p_y,p_z);
	mat4 rotationMatrix = rotation(0.0f,0.0f,1.0f,0.0f);
	mat4 scaleMatrix = scale(1.0f);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	pyramid = new Pyramid(1,1);
	pyramid->GenerateVerticesAndIndices();
	vertices = pyramid->GetVertices();
	indices = pyramid->GetIndices();
	programID = p_programID;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &indexBufferID);
	glGenBuffers(1, &vertexBufferID);
	inputManager = ServiceLocator<InputManager>::GetService();
	groundCollider = new TriangleGroundCollider(position.x,position.z);
	groundCollider->SetCollisionPoints( pyramid->GetGroundVertices() );
	noise = new PerlinNoise();
	circleCollider = new CircleCollider(position.x, position.z, 1.0f);
}
Ship::~Ship()
{
	delete pyramid;
	pyramid = nullptr;
	delete groundCollider;
	groundCollider = nullptr;
	delete noise;
	noise = nullptr;
	delete circleCollider;
	circleCollider = nullptr;

	glDeleteBuffers(1, &indexBufferID);
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vao);
}

float Ship::GetSpeed()
{
	return speed;
}

vec3 Ship::GetForwardVector()
{
	return forwardVector;
}

vec3 Ship::GetPosition()
{
	return position;
}

void Ship::Input(float p_delta)
{


}

void Ship::SetPosition(vec3 p_position)
{
	position = p_position;
}

CircleCollider* Ship::GetCircleCollider()
{
	return circleCollider;
}

vec3 Ship::GetMovementVector()
{
	return movementVector;
}

void Ship::Update(float p_delta)
{

	time += p_delta;
	float yNoise = noise->OctavePerlin((position.x)*0.1, (position.z)*0.1, time, 2, 1);

	if (inputManager->IsKeyDown(GLFW_KEY_A))
	{
		turnRate -= p_delta * 2.0f;
	}
	if (inputManager->IsKeyDown(GLFW_KEY_D))
	{
		turnRate += p_delta * 2.0f;
	}

	bool forward = false;
	if (inputManager->IsKeyDown(GLFW_KEY_W))
	{
		forward = true;
	}	

	mat4 translationMatrix = translation(position.x, position.y + yNoise, position.z);
	mat4 rotationMatrix = rotation(turnRate, 0.0f, 1.0f, 0.0f);
	forwardVector = { rotationMatrix.m20, rotationMatrix.m21, rotationMatrix.m22 };
	vec3 upVec = { rotationMatrix.m10,rotationMatrix.m11,rotationMatrix.m12 };
	
	modelMatrix = rotationMatrix;

	if (forward)
	{
		movementVector = forwardVector * p_delta * speed;
		position = position + forwardVector * p_delta * speed;
	}
	else
	{
		movementVector = { 0.0f,0.0f,0.0f };
	}
	
	std::vector<float> points = pyramid->GetGroundVertices();
	vec3 forwardPosition = { points[0],points[1],points[2] };
	vec3 backRightPosition = { points[7],points[4],points[5] };
	vec3 backLeftPosition = { points[6],points[7],points[8] };

	forwardPosition = modelMatrix * forwardPosition;
	backRightPosition = modelMatrix * backRightPosition;
	backLeftPosition = modelMatrix * backLeftPosition;

	float forwardNoise = noise->OctavePerlin((position.x + forwardPosition.x)*0.1, (position.z+forwardPosition.z)*0.1, time, 2, 1);
	forwardPosition = {forwardPosition.x,forwardPosition.y + forwardNoise,forwardPosition.z};
	float backRightNoise = noise->OctavePerlin((position.x+backRightPosition.x)*0.1, (position.z+backRightPosition.z)*0.1, time, 2, 1);
	backRightPosition = { backRightPosition.x,backRightPosition.y + backRightNoise, backRightPosition.z };
	float backLeftNoise = noise->OctavePerlin((position.x+backLeftPosition.x)*0.1, (position.z+backLeftPosition.z)*0.1, time, 2, 1);
	backLeftPosition = { backLeftPosition.x,backLeftPosition.y + backLeftNoise, backLeftPosition.z };
	
	//find midpoint between backright & back left?
	vec3 midPoint = (backRightPosition + backLeftPosition) / 2;
	midPoint = normalize(midPoint);
	vec3 normalForward = (normalize(forwardPosition) - midPoint);
	normalForward = normalize(normalForward);
	
	vec3 U = backRightPosition - forwardPosition;
	vec3 V = backLeftPosition - forwardPosition;

	vec3 normal = cross(U, V);
	normal = normalize(normal);

	//Now we need to find the angle difference between our triangles forward
	//and our ships current forward.
	vec3 sideVec = cross(normal,normalForward);
	sideVec = normalize(sideVec);

	mat4 secondRotationMatrix = { sideVec.x,sideVec.y,sideVec.z,0,
	normal.x,normal.y,normal.z,0,
	normalForward.x,normalForward.y,normalForward.z,0,
	0,0,0,1 };

	mat4 scaleMatrix = scale(1.0f);
	modelMatrix = translationMatrix*secondRotationMatrix*scaleMatrix;
	//here we can add scale.
	circleCollider->SetPosition(position.x, position.z);

}




void Ship::DrawShip() {
	glUseProgram(programID);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

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
		glUniformMatrix4fv(M, 1, false, m_myMatrix.m);
	}

	GLint Model = glGetUniformLocation(programID, "modelMatrix");
	if (Model != -1)
	{
		glUniformMatrix4fv(Model, 1, false, modelMatrix.m);
	}

	////////////////////////////////////////////////////////////

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);

	// Cleanup
	glDisableVertexAttribArray(P);
	glDisableVertexAttribArray(C);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Ship::SetMatrix(mat4 p_myMatrix)
{
	m_myMatrix = p_myMatrix;
}

