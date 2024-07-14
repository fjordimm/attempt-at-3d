
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

constexpr int INITIAL_WINDOW_WIDTH = 900;
constexpr int INITIAL_WINDOW_HEIGHT = 480;
constexpr char WINDOW_TITLE[] = "Test window";

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
	/* Create the window, initializing GLFW and GLEW */

	GLFWwindow* window;
	{
		if (!glfwInit())
		{ Debug::logFatalError("glfwInit failed."); }

		window = glfwCreateWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			Debug::logFatalError("glfwCreateWindow failed.");
		}

		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		glewInit();
	}

	/*  */

	GLuint vao;
	float verts1[] =
	{
		 0.0f,  0.5f,      1.0f,0.0f,0.0f,
		 0.5f, -0.5f,      0.0f,1.0f,0.0f,
		-0.5f, -0.5f,      0.0f,0.0f,1.0f
	};
	GLuint vbo;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLint posAttrib;
	GLint colAttrib;
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts1), verts1, GL_STATIC_DRAW);

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);
		checkShaderCompilation(vertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);
		checkShaderCompilation(fragmentShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);

		posAttrib = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

		colAttrib = glGetAttribLocation(shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	}

	/* Main Window Loop */

	while (!glfwWindowShouldClose(window))
    {
		/* Process inputs */

        /* Render stuff */

		glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Do stuff required by GLFW */

		glfwPollEvents();
        glfwSwapBuffers(window);
    }

	/* Deletions */

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	/* End */

    glfwTerminate();
    return 0;
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
