#pragma once
#include "5SD805_helper.h"

class WaterShader;
class BasicShader;
class BasicTexturedShader;
class FloatingShader;

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	GLuint& GetWaterShader();
	GLuint& GetBasicShader();
	GLuint& GetBasicTexturedShader();
	GLuint& GetFloatingShader();

private:
	WaterShader* waterShader;
	GLuint waterID;

	BasicShader* basicShader;
	GLuint basicID;

	BasicTexturedShader* basicTexturedShader;
	GLuint basicTexturedID;

	FloatingShader* floatingShader;
	GLuint floatingShaderID;
};

