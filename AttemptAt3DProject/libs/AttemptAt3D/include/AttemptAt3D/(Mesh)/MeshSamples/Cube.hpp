
#pragma once

#include "AttemptAt3D/(Mesh)/MeshSamples/MeshSample.hpp"

namespace AttemptAt3D::MeshSamples
{
	class Cube : public MeshSample
	{
	   protected:
		virtual std::size_t verticesSize() override; // In bytes, not length
		virtual const float* vertices() override;
		virtual std::size_t elementsSize() override; // In bytes, not length
		virtual const GLuint* elements() override;
	};
}
