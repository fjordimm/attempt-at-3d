
#include "AttemptAt3D/(Mesh)/Mesh.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Mesh::Mesh(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements) :
		verticesLen(verticesLen),
		vertices(std::move(vertices)),
		elementsLen(elementsLen),
		elements(std::move(elements))
	{}

	/* Methods */
}
