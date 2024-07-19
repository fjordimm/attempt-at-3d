
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>

namespace AttemptAt3D
{
	class ShaderManager
	{
		/* Fields */

	   private:
		GLuint vertexShader;
		GLuint geometryShader;
		GLuint fragmentShader;
		GLuint shaderProgram;
		GLint attrib_position;
		GLint attrib_color;
		GLint uni_model;
		GLint uni_view;
		GLint uni_proj;
		GLint uni_sunRot;

		/* Constructors */

	   public:
		ShaderManager(const ShaderManager&) = delete;
		ShaderManager& operator=(const ShaderManager&) = delete;
		
		ShaderManager();

		/* Methods */

	   public:
		void compileAndActivateShaders();
		void doVertexAttribPointers();
		void cleanupForGl();

	   private:
		void checkShaderCompilation(GLuint shader);
	};
}
