
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <list>
#include <memory>
#include "AttemptAt3D/BodyManager/_BodyManager/Body.hpp"
#include "AttemptAt3D/BodyManager/BodyReference.hpp"
#include "AttemptAt3D/ShaderManager/ShaderManager.hpp"

namespace AttemptAt3D
{
	class BodyManager
	{
		/* Fields */

	   private:
		std::list<std::unique_ptr<_BodyManager::Body>> bodies;

		/* Constructors */

	   public:
		BodyManager(const BodyManager&) = delete;
		BodyManager& operator=(const BodyManager&) = delete;
		
		BodyManager();

		/* Methods */

	   public:
		std::unique_ptr<BodyReference> addNewBody(ShaderManager& shaderManager, std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements);
		void removeBody(std::unique_ptr<BodyReference> bodyReference); // since the parameter is a unique_ptr to the BodyReference, it doesn't move it anywhere else so it implicitly deletes it
		void drawAllBodies(ShaderManager& shaderManager);
		void cleanupForGl();
	};
}
