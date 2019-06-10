#include "ShaderManager.h"
#include "BasicShader.h"
#include "BasicTexturedShader.h"
#include "WaterShader.h"
#include "FloatingShader.h"

ShaderManager::ShaderManager()
{
	waterShader = new WaterShader();
	waterID = waterShader->GetShader();

	basicShader = new BasicShader();
	basicID = basicShader->GetShader();

	basicTexturedShader = new BasicTexturedShader();
	basicTexturedID = basicTexturedShader->GetShader();

	floatingShader = new FloatingShader;
	floatingShaderID = floatingShader->GetShader();
}

ShaderManager::~ShaderManager()
{
	delete waterShader;
	waterShader = nullptr;
	delete basicShader;
	basicShader = nullptr;
	delete basicTexturedShader;
	basicTexturedShader = nullptr;
	delete floatingShader;
	floatingShader = nullptr;
}

GLuint& ShaderManager::GetWaterShader()
{
	return waterID;
}

GLuint& ShaderManager::GetBasicShader()
{
	return basicID;
}

GLuint& ShaderManager::GetBasicTexturedShader()
{
	return basicTexturedID;
}

GLuint& ShaderManager::GetFloatingShader()
{
	return floatingShaderID;
}