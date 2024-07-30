
#pragma once

#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/MeshSample.hpp"

namespace AttemptAt3D::MeshSamples
{
	class Cube : public MeshSample
	{
	   protected:
		virtual std::size_t verticesSize() const final; // In bytes, not length
		virtual const float* vertices() const final;
		virtual std::size_t elementsSize() const final; // In bytes, not length
		virtual const GLuint* elements() const final;
	};
}
