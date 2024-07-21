
#pragma once

#include <memory>
#include <cstdlib>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"
#include "AttemptAt3D/(Tran)/Tran.hpp"
#include "AttemptAt3D/(Mesh)/Mesh.hpp"
#include "AttemptAt3D/(ShaderManager)/ShaderManager.hpp"

namespace AttemptAt3D::_BodyManager
{
	class Body
	{
		/* Constructors */

	   public:
		Body() = delete;
		Body(const Body&) = delete;
		Body& operator=(const Body&) = delete;
		
		Body(Tran* tran, Mesh* mesh);

		/* Fields */

	   private:
		Tran* tran;
		Mesh* mesh;

		GLuint vao;
		GLuint vbo;
		GLuint ebo;

		/* Methods */

	   public:
		void initializeVao(ShaderManager& shaderManager);
		void drawBody(ShaderManager& shaderManager) const;
		void cleanupForGl();
	};
}
