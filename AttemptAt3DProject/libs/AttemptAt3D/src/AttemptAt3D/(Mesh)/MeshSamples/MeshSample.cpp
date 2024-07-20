
#include <cstring>
#include "AttemptAt3D/(Mesh)/MeshSamples/MeshSample.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D::MeshSamples
{
	/* Constructors */

	MeshSample::MeshSample() {}

	/* Functions */

	std::unique_ptr<Mesh> MeshSample::Make()
	{
		MeshSample inst;

		std::size_t vertsLen = inst.verticesSize() / sizeof(float);

		std::unique_ptr<float[]> verts(new float[vertsLen]);
		std::memcpy(verts.get(), inst.vertices(), inst.verticesSize());

		std::size_t elemsLen = inst.elementsSize() / sizeof(GLuint);

		std::unique_ptr<GLuint[]> elems(new GLuint[elemsLen]);
		std::memcpy(elems.get(), inst.elements(), inst.elementsSize());

		Debug::Log("vertices...");
		for (int i = 0; i < vertsLen; i++)
		{
			Debug::Printf("  %f\n", verts[i]);
		}

		Debug::Log("elements...");
		for (int i = 0; i < elemsLen; i++)
		{
			Debug::Printf("  %f\n", elems[i]);
		}

		return std::make_unique<Mesh>(vertsLen, std::move(verts), elemsLen, std::move(elems));
	}
}
