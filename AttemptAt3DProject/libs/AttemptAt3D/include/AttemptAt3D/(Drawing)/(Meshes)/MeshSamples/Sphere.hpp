
#pragma once

#include <cstdlib>
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/MeshSample.hpp"

namespace AttemptAt3D::MeshSamples
{
	template <std::size_t Size>
	class Sphere : public MeshSample
	{
	   protected:
		virtual std::size_t verticesSize() const override; // In bytes, not length
		virtual const float* vertices() const override;
		virtual std::size_t elementsSize() const override; // In bytes, not length
		virtual const GLuint* elements() const override;
	};
}
