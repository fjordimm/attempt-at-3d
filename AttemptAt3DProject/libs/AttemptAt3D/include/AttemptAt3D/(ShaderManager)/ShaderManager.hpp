
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
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

		/* Getters and Setters */

	   public:
		void set_uni_modelVal(const glm::mat4& val);
		void set_uni_viewVal(const glm::mat4& val);
		void set_uni_projVal(const glm::mat4& val);
		void set_uni_sunRotVal(const glm::mat4& val);

		/* Constructors */

	   public:
		ShaderManager(const ShaderManager&) = delete;
		ShaderManager& operator=(const ShaderManager&) = delete;
		
		ShaderManager();

		/* Methods */

	   public:
		void compileAndActivateShaders();
		void doAttribs();
		void cleanupForGl();

	   private:
		void checkShaderCompilation(GLuint shader);
	};
}
