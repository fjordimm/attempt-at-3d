
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
#include <chrono>
#include "CMakeConfig.h"
#include "AttemptAt3D/FileLoading/FileLoading.h"
#include "AttemptAt3D/Debug/Debug.h"

using namespace AttemptAt3D;

////////////////////////////////////////////////////////////

///// Constants /////

constexpr int INITIAL_WINDOW_WIDTH = 900;
constexpr int INITIAL_WINDOW_HEIGHT = 600;
constexpr char WINDOW_TITLE[] = "Test window";

constexpr char VERTEX_SHADER_SOURCE_PATH[] = "res/shaders/vertexShaderSource.glsl";
constexpr char FRAGMENT_SHADER_SOURCE_PATH[] = "res/shaders/fragmentShaderSource.glsl";

////////////////////////////////////////////////////////////

///// Forward Declarations /////

void checkShaderCompilation(GLuint shader);

////////////////////////////////////////////////////////////

///// Main Function /////

int main(void)
{
	/* Program Variables */

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

	/* OpenGL stuff */

	float verts1[] =
	{
		-0.3f,  0.3f,      1.0f,0.0f,0.0f,
		 0.3f,  0.3f,      0.0f,1.0f,0.0f,
		 0.3f, -0.3f,      0.0f,0.0f,1.0f,
		-0.3f, -0.3f,      0.0f,1.0f,1.0f
	};

	GLuint elems1[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLuint vao;
	GLuint ebo;
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

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elems1), elems1, GL_STATIC_DRAW);

		const char* vertexShaderSource = FileLoading::loadFile(VERTEX_SHADER_SOURCE_PATH);
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);
		checkShaderCompilation(vertexShader);
		delete[] vertexShaderSource;

		const char* fragmentShaderSource = FileLoading::loadFile(FRAGMENT_SHADER_SOURCE_PATH);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);
		checkShaderCompilation(fragmentShader);
		delete[] fragmentShaderSource;

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

	auto startTime = std::chrono::high_resolution_clock::now();

	while (!glfwWindowShouldClose(window))
    {
		/* Process inputs */

        /* Render stuff */

		glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		auto nowTime = std::chrono::high_resolution_clock::now();
		float timeElapsed = std::chrono::duration_cast<std::chrono::duration<float>>(nowTime - startTime).count();
		// std::cout << "time: " << timeElapsed << std::endl;
		verts1[0] = -0.3f - timeElapsed * 0.1f;
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts1), verts1, GL_STATIC_DRAW);

		/* Adjust the canvas when the window is resized */

		glfwSetWindowSizeCallback(window, [](GLFWwindow* _window, int _width, int _height)
		{ glViewport(0, 0, _width, _height); });

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

    glfwTerminate();
    return 0;
}

////////////////////////////////////////////////////////////

///// Helpers /////

void checkShaderCompilation(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status)
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
