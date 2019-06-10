#include "camera.h"
#include <iostream>


camera::camera()
{
	cameraPosition = { 0,0,0 };
	cameraForward = { 0,0,-1 };
	cameraUp = { 0,-1,0 };
}


camera::~camera()
{

}

void camera::SetCameraForward(vec3 p_forward)
{
	cameraForward = { p_forward.x,p_forward.y,p_forward.z };
}

void camera::SetCameraPosition(vec3 p_position)
{
	cameraPosition = { p_position.x,p_position.y,p_position.z };
}

void camera::Update(float p_targetX, float p_targetY, float p_targetZ) {

	projectionMatrix = perspective(PI*0.25f, 4.0f / 3, 0.1f, 10000);
	cameraPosition = { p_targetX,p_targetY,p_targetZ };
	cameraUp = { 0,-1,0 };
	cameraUp = normalize(cameraUp);
	vec3 sideVec = cross(cameraForward, cameraUp);
	sideVec = normalize(sideVec);
	viewMatrix = lookat(cameraPosition.x, cameraPosition.y, cameraPosition.z, cameraPosition.x + cameraForward.x, cameraPosition.y + cameraForward.y, cameraPosition.z + cameraForward.z, cameraUp.x, cameraUp.y, cameraUp.z);
}

void camera::LookAtTarget(float p_targetX, float p_targetY, float p_targetZ)
{
	projectionMatrix = perspective(PI*0.25f, 4.0f / 3, 0.1f, 10000);
	cameraPosition = { p_targetX,p_targetY,p_targetZ };
	cameraUp = { 0,-1,0 };
	cameraUp = normalize(cameraUp);
	cameraPosition = cameraPosition + (cameraForward * -10.0f) + cameraUp*7.5f;
	vec3 sideVec = cross(cameraForward, cameraUp);
	sideVec = normalize(sideVec);
	viewMatrix = lookat(cameraPosition.x, cameraPosition.y, cameraPosition.z, cameraPosition.x + cameraForward.x, cameraPosition.y+0.777 + cameraForward.y, cameraPosition.z + cameraForward.z, cameraUp.x, cameraUp.y, cameraUp.z);
}

mat4 camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

mat4 camera::GetViewMatrix()
{
	return viewMatrix;
}
