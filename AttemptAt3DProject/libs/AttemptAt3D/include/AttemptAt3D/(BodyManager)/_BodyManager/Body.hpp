
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include <cstdlib>
#include "AttemptAt3D/(Mesh)/Mesh.hpp"
#include "AttemptAt3D/(ShaderManager)/ShaderManager.hpp"

namespace AttemptAt3D::_BodyManager
{
	class Body
	{
		/* Fields */

	   public:
		glm::mat4 transform;

	   private:
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		std::unique_ptr<Mesh> mesh;

		/* Constructors */

	   public:
		Body(const Body&) = delete;
		Body& operator=(const Body&) = delete;
		
		Body();

		/* Methods */

	   public:
		void setMesh(std::unique_ptr<Mesh> mesh);
		void initializeVao(ShaderManager& shaderManager);
		void drawBody(ShaderManager& shaderManager);
		void cleanupForGl();
	};
}
