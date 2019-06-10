#pragma once
#include "5SD805_helper.h"

class BasicTexturedShader
{
public:
	BasicTexturedShader();
	~BasicTexturedShader();
	GLuint& GetShader();
private:
	GLuint programID;
	const char *vshCode;
	const char *fshCode;
};

