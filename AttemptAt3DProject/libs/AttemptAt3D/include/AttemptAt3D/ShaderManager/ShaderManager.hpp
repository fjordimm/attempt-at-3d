
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
		inline void change_uni_modelVal(glm::mat4 val) { glUniformMatrix4fv(this->uni_model, 1, GL_FALSE, glm::value_ptr(val)); }
		inline void change_uni_viewVal(glm::mat4 val) { glUniformMatrix4fv(this->uni_view, 1, GL_FALSE, glm::value_ptr(val)); }
		inline void change_uni_projVal(glm::mat4 val) { glUniformMatrix4fv(this->uni_proj, 1, GL_FALSE, glm::value_ptr(val)); }
		inline void change_uni_sunRotVal(glm::mat4 val) { glUniformMatrix4fv(this->uni_sunRot, 1, GL_FALSE, glm::value_ptr(val)); }

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
