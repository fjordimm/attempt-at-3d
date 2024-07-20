
#include "AttemptAt3D/(Mesh)/MeshSamples/InvertedPyramid.hpp"

namespace AttemptAt3D::MeshSamples
{
	static constexpr float VERTICES[] =
	{
		// X      Y      Z         R    G    B
		-0.3f, +0.3f, +0.8f,     1.0f,0.0f,0.0f,
		-0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
		+0.3f, +0.3f, +0.8f,     1.0f,0.0f,0.0f,
		+0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
		
		-0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
		+0.0f, +0.0f, +0.0f,     1.0f,0.0f,0.0f,
		+0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
		
		+0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
		+0.0f, +0.0f, +0.0f,     1.0f,0.0f,0.0f,
		+0.3f, +0.3f, +0.8f,     1.0f,0.0f,0.0f,
	};

	static constexpr GLuint ELEMENTS[] =
	{
		0, 1, 2,
		3, 2, 1,

		4, 5, 6,

		7, 8, 9
	};
	
	std::size_t InvertedPyramid::verticesSize()
	{ return sizeof(VERTICES); }

	const float* InvertedPyramid::vertices()
	{ return VERTICES; }

	std::size_t InvertedPyramid::elementsSize()
	{ return sizeof(ELEMENTS); }

	const GLuint* InvertedPyramid::elements()
	{ return ELEMENTS; }
}
