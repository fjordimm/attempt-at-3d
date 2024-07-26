
#pragma once

#include "AttemptAt3D/(Drawing)/MeshSamples/MeshSample.hpp"

namespace AttemptAt3D::MeshSamples
{
	class InvertedPyramid : public MeshSample
	{
	   protected:
		virtual std::size_t verticesSize() const override; // In bytes, not length
		virtual const float* vertices() const override;
		virtual std::size_t elementsSize() const override; // In bytes, not length
		virtual const GLuint* elements() const override;
	};
}
