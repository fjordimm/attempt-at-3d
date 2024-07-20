
#include "AttemptAt3D/(Mesh)/Mesh.hpp"

#include <sstream>

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

	std::string Mesh::toString() const
	{
		std::ostringstream ret;

		ret << "Mesh:\n";

		ret << "  Vertices (" << this->verticesLen << "):\n    ";
		for (int i = 0; i < this->verticesLen; i++)
		{
			if (i > 0) { ret << ", "; }
			ret << this->vertices[i];
		}
		ret << "\n";

		ret << "  Elements (" << this->elementsLen << "):\n    ";
		for (int i = 0; i < this->elementsLen; i++)
		{
			if (i > 0) { ret << ", "; }
			ret << this->elements[i];
		}

		return ret.str();
	}
}
