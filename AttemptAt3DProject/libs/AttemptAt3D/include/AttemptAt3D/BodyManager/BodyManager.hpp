
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <list>
#include <memory>
#include "AttemptAt3D/BodyManager/Body.hpp"

namespace AttemptAt3D
{
	class BodyManager
	{
		/* Forward Declarations */

	   public:
		class BodyReference;

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
		std::unique_ptr<BodyReference> addNewBody(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements);
		void removeBody(std::unique_ptr<BodyReference> bodyReference); // since the parameter is a unique_ptr to the BodyReference, it doesn't move it anywhere else so it implicitly deletes it
		void drawAllBodies();
		void cleanupForGl();

		/* Subclasses */

	   public:
		class BodyReference
		{
			friend class BodyManager;

			/* Fields */

		   private:
			std::list<std::unique_ptr<_BodyManager::Body>>::const_iterator iter; // since there is no way to get a node for std::list, I use an iterator with the cursor at the current element which has the same functionality

			/* Constructors */

		   public:
			BodyReference(const BodyReference&) = delete;
			BodyReference& operator=(const BodyReference&) = delete;
			
			BodyReference();
		};
	};
}
