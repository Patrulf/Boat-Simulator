#pragma once
#include "5SD805_helper.h"

class BasicShader
{
public:
	BasicShader();
	~BasicShader();
	GLuint& GetShader();
private:
	GLuint programID;
	const char *vshCode;
	const char *fshCode;
};

