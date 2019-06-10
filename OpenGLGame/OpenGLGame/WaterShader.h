#pragma once
#include "5SD805_helper.h"

class WaterShader
{
public:
	WaterShader();
	~WaterShader();
	GLuint& GetShader();
private:
	GLuint programID;
	const char *vshCode;
	const char *fshCode;
};

