
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <cstdlib>
#include "AttemptAt3D/(Mesh)/Mesh.hpp"

namespace AttemptAt3D::MeshSamples
{
	class MeshSample
	{
		/* Constructors */

	   public:
		MeshSample(const MeshSample&) = delete;
		MeshSample& operator=(const MeshSample&) = delete;

	   protected:
		MeshSample();

		/* Methods */

	   protected:
		virtual std::size_t verticesSize() { return 0; } // In bytes, not length
		virtual const float* vertices() { return nullptr; }
		virtual std::size_t elementsSize() { return 0; } // In bytes, not length
		virtual const GLuint* elements() { return nullptr; }

		/* Functions */

	   public:
		static std::unique_ptr<Mesh> Make();
	};
}
