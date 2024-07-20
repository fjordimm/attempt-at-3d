
#pragma once

#include "AttemptAt3D/(Mesh)/MeshSamples/MeshSample.hpp"

namespace AttemptAt3D::MeshSamples
{
	class Cube : public MeshSample
	{
	   protected:
		virtual std::size_t verticesSize(); // In bytes, not length
		virtual const float* vertices();
		virtual std::size_t elementsSize(); // In bytes, not length
		virtual const GLuint* elements();
	};
}
