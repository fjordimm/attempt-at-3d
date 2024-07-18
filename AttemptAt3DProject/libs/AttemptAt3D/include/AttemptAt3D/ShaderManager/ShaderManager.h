
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AttemptAt3D
{
	class ShaderManager
	{
		/* Fields */

	   private:
		int a;

		/* Constructors */

	   public:
		ShaderManager(const ShaderManager&) = delete;
		ShaderManager& operator=(const ShaderManager&) = delete;
		ShaderManager(ShaderManager&&) {}
		
		ShaderManager();

		/* Methods */
	};
}
