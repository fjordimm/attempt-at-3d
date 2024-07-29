
#include <cstring>
#include "AttemptAt3D/(Drawing)/MeshSamples/MeshSample.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D::MeshSamples
{
	/* Constructors */

	MeshSample::MeshSample() {}

	/* Methods */

	std::unique_ptr<MeshData> MeshSample::make() const
	{
		std::size_t vertsLen = this->verticesSize() / sizeof(float);

		std::unique_ptr<float[]> verts(new float[vertsLen]);
		std::memcpy(verts.get(), this->vertices(), this->verticesSize());

		std::size_t elemsLen = this->elementsSize() / sizeof(GLuint);

		std::unique_ptr<GLuint[]> elems(new GLuint[elemsLen]);
		std::memcpy(elems.get(), this->elements(), this->elementsSize());

		return std::make_unique<MeshData>(vertsLen, std::move(verts), elemsLen, std::move(elems));
	}
}
