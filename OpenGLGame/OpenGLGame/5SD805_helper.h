#pragma once

#include "glew.h"
#include "glfw3.h"
#include <inttypes.h>
typedef uint32_t uint;
typedef uint16_t ushort;

#include <assert.h>
#include "5SD805_math.h"

#define KiloBytes(a) ((a) * 1024)
#define MegaBytes(a) ((a) * KiloBytes(1024))

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
#define BufferOffset(bytes) ((char *)NULL + (bytes))

static double map(double i, double a, double b, double A, double B) {
	return A + (B - A) * ((i - a) / (b - a));
}

// hue [0,360] well, any number wors as I wrap it
// saturation [0,1] grey->fully saturated
// lightness [0,1] black->white
static void hsv2rgb(float hue, float saturation, float lightness, float *r, float *g, float *b) {
	if (saturation < 0.f) saturation = 0.f;
	if (saturation > 1.f) saturation = 1.f;
	if (lightness < 0.f) lightness = 0.f;
	if (lightness > 1.f) lightness = 1.f;
	while (hue <0) {
		hue += 360.f;
	}
	while (hue >= 360.f) {
		hue -= 360.f;
	}

	float h = hue / 60.f;
	int i = (int)h;
	float fraction = h - (float)i;

	float p = lightness * (1.0 - saturation);
	float q = lightness * (1.0 - (saturation * fraction));
	float t = lightness * (1.0 - (saturation * (1.0 - fraction)));

	switch (i) {
	case 0:
		*r = lightness;
		*g = t;
		*b = p;
		break;
	case 1:
		*r = q;
		*g = lightness;
		*b = p;
		break;
	case 2:
		*r = p;
		*g = lightness;
		*b = t;
		break;
	case 3:
		*r = p;
		*g = q;
		*b = lightness;
		break;
	case 4:
		*r = t;
		*g = p;
		*b = lightness;
		break;
	case 5:
	default:
		*r = lightness;
		*g = p;
		*b = q;
		break;
	}
}
static vec3 hsv2rgb(float hue, float saturation, float lightness) {
	vec3 c;
	hsv2rgb(hue, saturation, lightness, &c.r, &c.g, &c.b);
	return c;
}


//----------------------------------------------------------------------
//                            OpenGL
//----------------------------------------------------------------------


static void _DumpGLErrors(const char *file, int line) {
	line--;
	GLenum error = glGetError();
	switch (error) {
	case GL_INVALID_ENUM: printf("GL ERROR: GL_INVALID_ENUM @file: %s @line:%d\n", file, line); break;
	case GL_INVALID_VALUE: printf("GL ERROR: GL_INVALID_VALUE @file: %s @line:%d\n", file, line); break;
	case GL_INVALID_OPERATION: printf("GL ERROR: GL_INVALID_OPERATION @file: %s @line:%d\n", file, line); break;
	case GL_INVALID_FRAMEBUFFER_OPERATION: printf("GL ERROR: GL_INVALID_FRAMEBUFFER_OPERATION @file: %s @line:%d\n", file, line); break;
	case GL_OUT_OF_MEMORY: printf("GL ERROR: GL_OUT_OF_MEMORY @file: %s @line:%d\n", file, line); break;
	case GL_NO_ERROR:
		// printf("GL_NO_ERROR @ %s %s %d\n", proc, file, line); break;
	default:
		break;
	}
}

#define DumpGLErrors() _DumpGLErrors(__FILE__, __LINE__)


static GLuint CreateProgram(const char *vshCode, const char *fshCode) {
	// COMPILE VERTEX SHADER
	GLuint vshID = glCreateShader(GL_VERTEX_SHADER);
	DumpGLErrors();
	assert(glIsShader(vshID));
	glShaderSource(vshID, 1, (const GLchar**)&vshCode, 0);
	DumpGLErrors();
	glCompileShader(vshID);
	DumpGLErrors();
	GLint vshIsCompiled;

	glGetShaderiv(vshID, GL_COMPILE_STATUS, &vshIsCompiled);
	DumpGLErrors();
	if (!vshIsCompiled) {
		GLsizei length;
		char buffer[4096];
		glGetShaderInfoLog(vshID, sizeof(buffer), &length, buffer);
		DumpGLErrors();
		if (length > 0) printf("Vertex shader compile errors: \n%s\n", buffer);
		assert(!"Vertex shader compilation failed!");
	}

	// COMPILE FRAGMENT SHADER
	GLuint fshID = glCreateShader(GL_FRAGMENT_SHADER);
	DumpGLErrors();
	glShaderSource(fshID, 1, (const GLchar**)&fshCode, 0);
	DumpGLErrors();
	assert(glIsShader(fshID));
	glCompileShader(fshID);
	DumpGLErrors();
	GLint fshIsCompiled;
	glGetShaderiv(fshID, GL_COMPILE_STATUS, &fshIsCompiled);
	DumpGLErrors();
	if (!fshIsCompiled) {
		GLsizei length;
		char buffer[4096];
		glGetShaderInfoLog(fshID, sizeof(buffer), &length, buffer);
		DumpGLErrors();
		if (length > 0) printf("Fragment shader compile errors: \n%s\n", buffer);
		assert(!"Fragment shader compilation failed!");
	}

	// LINK
	GLuint programID = glCreateProgram();
	assert(glIsProgram(programID));
	glAttachShader(programID, vshID);
	glAttachShader(programID, fshID);
	glLinkProgram(programID);

	glValidateProgram(programID);
	GLint isLinked;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);

	if (!isLinked) {
		GLsizei length;
		char buffer[4096];
		glGetProgramInfoLog(programID, sizeof(buffer), &length, buffer);
		if (length > 0) printf("Program link errors: \n%s\n", buffer);
		assert(!"Program linking failed");
	}

	glDeleteShader(vshID);
	glDeleteShader(fshID);

	return programID;
}

//Create program with geometry shader.
static GLuint CreateProgram(const char *vshCode,const char *gshCode, const char *fshCode) {
	// COMPILE VERTEX SHADER
	GLuint vshID = glCreateShader(GL_VERTEX_SHADER);
	DumpGLErrors();
	assert(glIsShader(vshID));
	glShaderSource(vshID, 1, (const GLchar**)&vshCode, 0);
	DumpGLErrors();
	glCompileShader(vshID);
	DumpGLErrors();
	GLint vshIsCompiled;

	glGetShaderiv(vshID, GL_COMPILE_STATUS, &vshIsCompiled);
	DumpGLErrors();
	if (!vshIsCompiled) {
		GLsizei length;
		char buffer[4096];
		glGetShaderInfoLog(vshID, sizeof(buffer), &length, buffer);
		DumpGLErrors();
		if (length > 0) printf("Vertex shader compile errors: \n%s\n", buffer);
		assert(!"Vertex shader compilation failed!");
	}

	// COMPILE GEOMETRY SHADER
	GLuint gshID = glCreateShader(GL_GEOMETRY_SHADER);
	DumpGLErrors();
	assert(glIsShader(gshID));
	glShaderSource(gshID, 1, (const GLchar**)&gshCode, 0);
	DumpGLErrors();
	glCompileShader(gshID);
	DumpGLErrors();
	GLint gshIsCompiled;

	glGetShaderiv(gshID, GL_COMPILE_STATUS, &gshIsCompiled);
	DumpGLErrors();
	if (!gshIsCompiled) {
		GLsizei length;
		char buffer[4096];
		glGetShaderInfoLog(gshID, sizeof(buffer), &length, buffer);
		DumpGLErrors();
		if (length > 0) printf("Geometry shader compile errors: \n%s\n", buffer);
		assert(!"Geometry shader compilation failed!");
	}

	// COMPILE FRAGMENT SHADER
	GLuint fshID = glCreateShader(GL_FRAGMENT_SHADER);
	DumpGLErrors();
	glShaderSource(fshID, 1, (const GLchar**)&fshCode, 0);
	DumpGLErrors();
	assert(glIsShader(fshID));
	glCompileShader(fshID);
	DumpGLErrors();
	GLint fshIsCompiled;
	glGetShaderiv(fshID, GL_COMPILE_STATUS, &fshIsCompiled);
	DumpGLErrors();
	if (!fshIsCompiled) {
		GLsizei length;
		char buffer[4096];
		glGetShaderInfoLog(fshID, sizeof(buffer), &length, buffer);
		DumpGLErrors();
		if (length > 0) printf("Fragment shader compile errors: \n%s\n", buffer);
		assert(!"Fragment shader compilation failed!");
	}

	// LINK
	GLuint programID = glCreateProgram();
	assert(glIsProgram(programID));
	glAttachShader(programID, vshID);
	glAttachShader(programID, gshID);
	glAttachShader(programID, fshID);
	glLinkProgram(programID);

	glValidateProgram(programID);
	GLint isLinked;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);

	if (!isLinked) {
		GLsizei length;
		char buffer[4096];
		glGetProgramInfoLog(programID, sizeof(buffer), &length, buffer);
		if (length > 0) printf("Program link errors: \n%s\n", buffer);
		assert(!"Program linking failed");
	}

	glDeleteShader(vshID);
	glDeleteShader(gshID);
	glDeleteShader(fshID);

	return programID;
}
