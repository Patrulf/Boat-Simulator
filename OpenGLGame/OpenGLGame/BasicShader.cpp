#include "BasicShader.h"

BasicShader::BasicShader()
{
	vshCode = R"BLAH(
  #version 330
	in vec3 vPositions;
	in vec3 colors;
	out vec4 myColor;
	uniform mat4 myMat;	
	uniform mat4 modelMatrix;

  void main(){	
	myColor = vec4(colors,1);
	gl_Position = myMat * modelMatrix * vec4((vPositions), 1.0);
  }
  )BLAH";


	fshCode = R"BLAH(
  #version 330
	out vec4 fragColor;
	in vec4 myColor;

void main(){
	fragColor = myColor;  
}
  )BLAH";

	programID = CreateProgram(vshCode, fshCode);
}

GLuint& BasicShader::GetShader()
{
	return programID;
}

BasicShader::~BasicShader()
{
	glDeleteProgram(programID);
	vshCode = nullptr;
	fshCode = nullptr;
}
