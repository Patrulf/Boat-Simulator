#pragma once
#include "5SD805_helper.h"

class FloatingShader
{
public:
	FloatingShader();
	~FloatingShader();
	GLuint& GetShader();
private:
	GLuint programID;
	const char *vshCode;
	const char *fshCode;
};