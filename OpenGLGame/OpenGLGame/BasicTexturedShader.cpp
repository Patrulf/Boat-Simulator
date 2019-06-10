#include "BasicTexturedShader.h"

BasicTexturedShader::BasicTexturedShader()
{
	vshCode = R"BLAH(
  #version 330
	in vec3 vPositions;
	in vec2 uvs;
	in vec3 colors;
	out vec4 myColor;
	uniform mat4 myMat;	
	uniform mat4 modelMatrix;

	out vec2 fuvs;

  void main(){	
	myColor = vec4(colors,1);
	gl_Position = myMat * modelMatrix * vec4((vPositions), 1.0);
	fuvs = uvs;
  }
  )BLAH";


	fshCode = R"BLAH(
  #version 330
	out vec4 fragColor;
	in vec4 myColor;
	in vec2 fuvs;

	uniform sampler2D ourTexture;

void main(){	
	fragColor = texture(ourTexture, fuvs);
}
  )BLAH";
	programID = CreateProgram(vshCode, fshCode);
}

GLuint& BasicTexturedShader::GetShader()
{
	return programID;
}

BasicTexturedShader::~BasicTexturedShader()
{
	glDeleteProgram(programID);
	vshCode = nullptr;
	fshCode = nullptr;
}
