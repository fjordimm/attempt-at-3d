
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

		MeshSample();

		/* Methods */

	   public:
		std::unique_ptr<Mesh> make();

	   protected:
		virtual std::size_t verticesSize() = 0; // In bytes, not length
		virtual const float* vertices() = 0;
		virtual std::size_t elementsSize() = 0; // In bytes, not length
		virtual const GLuint* elements() = 0;
	};
}
