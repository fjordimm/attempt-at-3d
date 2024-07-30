
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/Cube.hpp"

namespace AttemptAt3D::MeshSamples
{
	static constexpr float VERTICES[] =
	{
		// X      Y      Z
		 -1.0f, +1.0f, -1.0f,
		 +1.0f, +1.0f, -1.0f,
		 -1.0f, -1.0f, -1.0f,
		 +1.0f, -1.0f, -1.0f,
		 
		 -1.0f, +1.0f, +1.0f,
		 +1.0f, +1.0f, +1.0f,
		 -1.0f, -1.0f, +1.0f,
		 +1.0f, -1.0f, +1.0f,
	};

	static constexpr GLuint ELEMENTS[] =
	{
		// bottom
		0, 3, 2,
		3, 0, 1,

		// top
		6, 5, 4,
		5, 6, 7,

		// front
		2, 7, 6,
		7, 2, 3,

		// back
		1, 4, 5,
		4, 1, 0,

		// left
		0, 6, 4,
		6, 0, 2,

		// right
		3, 5, 7,
		5, 3, 1
	};
	
	std::size_t Cube::verticesSize() const
	{ return sizeof(VERTICES); }

	const float* Cube::vertices() const
	{ return VERTICES; }

	std::size_t Cube::elementsSize() const
	{ return sizeof(ELEMENTS); }

	const GLuint* Cube::elements() const
	{ return ELEMENTS; }
}
