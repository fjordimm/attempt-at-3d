
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/MeshSample.hpp"

#include <cstring>
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D::MeshSamples
{
	/* Constructors */

	MeshSample::MeshSample() {}

	/* Methods */

	std::unique_ptr<MeshData> MeshSample::make(MeshVertexAttributes attribs) const
	{
		bool doPositions3D = (attribs & MeshVertexAttributes::Positions3D) != MeshVertexAttributes::None;
		bool doNormals3D = (attribs & MeshVertexAttributes::Normals3D) != MeshVertexAttributes::None;

		if (!doPositions3D)
		{ Debug::LogFatalError("Tried to make a mesh with no position attribute."); }

		/* Make verts */

		std::size_t vertsLen = -1;
		std::unique_ptr<float[]> verts(nullptr);
		{
			std::unique_ptr<const std::vector<Vec>> vertPositions = nullptr;
			if (doPositions3D)
			{ vertPositions = this->vertPositions(); }

			std::unique_ptr<const std::vector<Vec>> vertNormals = nullptr;
			if (doNormals3D)
			{ vertNormals = this->vertNormals(); }

			if
		}

		/* Make elems */


		///////////////////////////////////

		// std::size_t vertsLen = this->verticesSize() / sizeof(float);

		// std::unique_ptr<float[]> verts(new float[vertsLen]);
		// std::memcpy(verts.get(), this->vertices(), this->verticesSize());

		// std::size_t elemsLen = this->elementsSize() / sizeof(GLuint);

		// std::unique_ptr<GLuint[]> elems(new GLuint[elemsLen]);
		// std::memcpy(elems.get(), this->elements(), this->elementsSize());

		// return std::make_unique<MeshData>(vertsLen, std::move(verts), elemsLen, std::move(elems));
	}

	/* Enum Operator Overloads */

	MeshSample::MeshVertexAttributes operator|(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshSample::MeshVertexAttributes rhs)
	{
		return static_cast<MeshSample::MeshVertexAttributes>(
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(lhs) |
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(rhs)
		);
	}

	MeshSample::MeshSample::MeshVertexAttributes operator&(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshVertexAttributes rhs)
	{
		return static_cast<MeshSample::MeshVertexAttributes>(
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(lhs) &
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(rhs)
		);
	}

	MeshSample::MeshSample::MeshVertexAttributes operator^(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshVertexAttributes rhs)
	{
		return static_cast<MeshSample::MeshVertexAttributes>(
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(lhs) ^
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(rhs)
		);
	}

	MeshSample::MeshSample::MeshVertexAttributes operator~(MeshSample::MeshVertexAttributes the)
	{
		return static_cast<MeshSample::MeshVertexAttributes>(
			~static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(the)
		);
	}

	bool operator==(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshVertexAttributes rhs)
	{
		return
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(lhs) ==
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(rhs);
	}

	bool operator!=(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshVertexAttributes rhs)
	{
		return
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(lhs) !=
			static_cast<std::underlying_type_t<MeshSample::MeshVertexAttributes>>(rhs);
	}
}
