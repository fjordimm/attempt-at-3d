
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/InvertedPyramid.hpp"

namespace AttemptAt3D::MeshSamples
{
	static constexpr float VERTICES[] =
	{
		// X      Y      Z         R    G    B
		 -0.3f, +0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 -0.3f, -0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 +0.3f, +0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 +0.3f, -0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 
		 -0.3f, -0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 +0.0f, +0.0f, +0.0f,     1.0f,1.0f,1.0f,
		 +0.3f, -0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 
		 +0.3f, -0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 +0.0f, +0.0f, +0.0f,     1.0f,1.0f,1.0f,
		 +0.3f, +0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 
		 +0.3f, +0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 +0.0f, +0.0f, +0.0f,     1.0f,1.0f,1.0f,
		 -0.3f, +0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 
		 -0.3f, +0.3f, +0.8f,     1.0f,1.0f,1.0f,
		 +0.0f, +0.0f, +0.0f,     1.0f,1.0f,1.0f,
		 -0.3f, -0.3f, +0.8f,     1.0f,1.0f,1.0f,
	};

	static constexpr GLuint ELEMENTS[] =
	{
		0, 1, 2,
		3, 2, 1,

		4, 5, 6,
		7, 8, 9,
		10, 11, 12,
		13, 14, 15
	};
	
	std::size_t InvertedPyramid::verticesSize() const
	{ return sizeof(VERTICES); }

	const float* InvertedPyramid::vertices() const
	{ return VERTICES; }

	std::size_t InvertedPyramid::elementsSize() const
	{ return sizeof(ELEMENTS); }

	const GLuint* InvertedPyramid::elements() const
	{ return ELEMENTS; }
}
