
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

namespace AttemptAt3D
{
	class DrawObj
	{
		/* Constructors */

	   public:
		DrawObj() = delete;
		DrawObj(const DrawObj&) = delete;
		DrawObj& operator=(const DrawObj&) = delete;

		DrawObj(ShaderManager& shaderManager, Tran* tran, Mesh* mesh);

		/* Fields */

	   private:
		Tran* tran;
		Mesh* mesh;

		GLuint vao;
		GLuint vbo;
		GLuint ebo;

		/* Methods */

	   public:
		void draw(ShaderManager& shaderManager) const;
		void cleanupForGl();
	};
}
