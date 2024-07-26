
#pragma once

#include <memory>
#include <cstdlib>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AttemptAt3D/(Drawing)/MeshData.hpp"

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
		std::unique_ptr<MeshData> make() const;

	   protected:
		virtual std::size_t verticesSize() const = 0; // In bytes, not length
		virtual const float* vertices() const = 0;
		virtual std::size_t elementsSize() const = 0; // In bytes, not length
		virtual const GLuint* elements() const = 0;
	};
}
