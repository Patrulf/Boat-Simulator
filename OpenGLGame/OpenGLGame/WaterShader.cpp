#include "WaterShader.h"

WaterShader::WaterShader()
{
	vshCode = R"BLAH(
  #version 330
	uniform float time;
	in vec3 vPositions;
	in vec3 colors;
	out vec4 myColor;
	uniform mat4 myMat;
	uniform mat4 modelMatrix;

float Fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float lerp(float p_t, float p_a, float p_b)
{
	return p_a + p_t * (p_b - p_a);
}

float Grad(int p_hash, float p_x, float p_y, float p_z)
{
	int h = p_hash & 15;
	float u = h<8 ? p_x : p_y,
		v = h<4 ? p_y : h == 12 || h == 14 ? p_x : p_z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float PerlinNoise(float p_x, float p_y, float p_z)
{
	int permutation[256] = int[] ( 151,160,137,91,90,15,
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 );

	int p[512];
	int i = 0;
	for (int i = 0; i < 256; i++)
	{
				p[256 + i] = permutation[i];
				p[i] = permutation[i];
	}

	int x = int(floor(p_x)) & 255;
	int y = int(floor(p_y)) & 255;
	int z = int(floor(p_z)) & 255;

	p_x -= floor(p_x);
	p_y -= floor(p_y);
	p_z -= floor(p_z);

	float u = Fade(p_x);
	float v = Fade(p_y);
	float w = Fade(p_z);

	int A = p[x] + y, AA = p[A] + z, AB = p[A + 1] + z,
		B = p[x + 1] + y, BA = p[B] + z, BB = p[B + 1] + z;

	return lerp(w, lerp(v, lerp(u, Grad(p[AA], p_x, p_y, p_z),
								Grad(p[BA], p_x - 1, p_y, p_z)),
								lerp(u, Grad(p[AB], p_x, p_y - 1, p_z),
								Grad(p[BB], p_x - 1, p_y - 1, p_z))),
								lerp(v, lerp(u, Grad(p[AA + 1], p_x, p_y, p_z - 1),
								Grad(p[BA + 1], p_x - 1, p_y, p_z - 1)),
								lerp(u, Grad(p[AB + 1], p_x, p_y - 1, p_z - 1),
								Grad(p[BB + 1], p_x - 1, p_y - 1, p_z - 1))));
}

float OctavePerlin(float x, float y, float z, int octaves, float persistence) {
    float total = 0;
    float frequency = 1;
    float amplitude = 1;
    float maxValue = 0;

	int i= 0;
    for(i=0;i<octaves;i++) {
        total += PerlinNoise(x * frequency, y * frequency, z * frequency) * amplitude;
        
        maxValue += amplitude;
        
        amplitude *= persistence;
        frequency *= 2;
    }
    
    return total/maxValue;
}

  void main(){	

	float noise = OctavePerlin((vPositions.x)*0.1,(vPositions.z)*0.1,time,2,1.0);

	myColor = vec4(0.1,0,0.5 + (noise*0.5*-1),1.0);
	myColor = vec4(myColor.x,myColor.y,myColor.z,1.0);

	vec3 pos = vec3(vPositions.x,vPositions.y+noise, vPositions.z);
	gl_Position = myMat * modelMatrix * vec4((pos), 1.0);
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

GLuint& WaterShader::GetShader()
{
	return programID;
}

WaterShader::~WaterShader()
{
	glDeleteProgram(programID);
	vshCode = nullptr;
	fshCode = nullptr;
}
