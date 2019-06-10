#pragma once

#include "5SD805_math.h"
#include "Ship.h"

class camera
{
public:
	void LookAtTarget(float p_targetX, float p_targetY, float p_targetZ);
	camera();
	~camera();
	mat4 GetProjectionMatrix();
	mat4 GetViewMatrix();
	void SetCameraForward(vec3 p_forward);
	void SetCameraPosition(vec3 p_position);
	void Update(float p_targetX, float p_targetY, float p_targetZ);

private:
	mat4 projectionMatrix;
	mat4 viewMatrix;

	vec3 cameraPosition;
	vec3 cameraForward;
	vec3 cameraUp;
	
};

