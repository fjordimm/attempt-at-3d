
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AttemptAt3D/BodyManager/Body.h"
#include <list>

// TODO: reorganize the order of private/public in classes

namespace AttemptAt3D
{
	class BodyManager
	{
	public:
		class BodyReference; // Forward declaration

		BodyManager();
		~BodyManager();
		BodyManager(const BodyManager&) = delete;
		BodyManager& operator=(const BodyManager&) = delete;

		std::unique_ptr<BodyReference> makeNewBody(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements);
		void removeBody(std::unique_ptr<BodyReference> bodyReference); // since the parameter is a unique_ptr to the BodyReference, it doesn't move it anywhere else so it implicitly deletes it
		void drawAllBodies();

		class BodyReference
		{
			friend class BodyManager;

		private:
			std::list<_BodyManager::Body>::iterator iter; // since there is no node type for std::list, I use an iterator with the cursor at the current element which has the same functionality

			BodyReference();
			~BodyReference();
			BodyReference(const BodyReference&) = delete;
			BodyReference& operator=(const BodyReference&) = delete;
		};
	
	private:
		std::list<_BodyManager::Body> bodies;
	};
}
