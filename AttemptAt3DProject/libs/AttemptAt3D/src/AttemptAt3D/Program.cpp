
////////////////////////////////////////////////////////////

///// Includes /////

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include "CMakeConfig.h"
#include "AttemptAt3D/FileLoading/FileLoading.h"
#include "AttemptAt3D/Debug/Debug.h"

using namespace AttemptAt3D;

////////////////////////////////////////////////////////////

///// Constants /////

const char* vertexShaderSource = R"glsl(
	#version 150 core

	in vec2 position;
	in vec3 color;

	out vec3 Color;

	void main()
	{
		Color = color;
		gl_Position = vec4(position, 0.0, 1.0);
	}
)glsl";

const char* fragmentShaderSource = R"glsl(
	#version 150 core

	in vec3 Color;

	out vec4 outColor;

	void main()
	{
		outColor = vec4(Color, 1.0);
	}
)glsl";

////////////////////////////////////////////////////////////

///// Forward Declarations /////

void checkShaderCompilation(GLuint shader);

////////////////////////////////////////////////////////////

///// Main Function /////

int main(void)
{
	Debug::logFatalError("burjhdh");

	/* Create the window, initializing GLFW and GLEW */

	// GLFWwindow* window;
	// {
	// 	if (!glfwInit())
	// 	{ throw  }
	// }
}

////////////////////////////////////////////////////////////

///// Helpers /////

void checkShaderCompilation(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == true)
	{ return; }
	else
	{
		static char buf[512];
		glGetShaderInfoLog(shader, 512, nullptr, buf);
		std::fprintf(stderr, "=== Shader did not compile ===\n");
		std::fprintf(stderr, "%s\n", buf);
		std::exit(EXIT_FAILURE);
	}
}

////////////////////////////////////////////////////////////
