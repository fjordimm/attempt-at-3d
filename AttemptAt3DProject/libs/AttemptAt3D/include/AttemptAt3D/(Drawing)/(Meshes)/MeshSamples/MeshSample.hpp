
#pragma once

#include <memory>
#include <vector>
#include <cstdlib>
#include <type_traits>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshData.hpp"
#include "AttemptAt3D/(Util)/(Tran)/Vec.hpp"

namespace AttemptAt3D::MeshSamples
{
	class MeshSample
	{
		/* Enums */

	   public:
		enum class MeshVertexAttributes : std::uint32_t
		{
			None        = 0u,
			Positions3D = 1u << 1,
			Normals3D   = 1u << 2
		};

		/* Constructors */

	   public:
		MeshSample(const MeshSample&) = delete;
		MeshSample& operator=(const MeshSample&) = delete;

		MeshSample();

		/* Methods */

	   public:
		std::unique_ptr<MeshData> make(MeshVertexAttributes attribs = MeshVertexAttributes::Positions3D) const;

	   protected:
		virtual std::unique_ptr<const std::vector<Vec>> vertPositions() const = 0;
		virtual std::unique_ptr<const std::vector<Vec>> vertNormals() const = 0;
		virtual std::unique_ptr<const std::vector<GLuint>> triangles() const = 0;
	};

	/* Enum Operator Overloads */

	MeshSample::MeshVertexAttributes operator|(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshVertexAttributes rhs);
	MeshSample::MeshVertexAttributes operator&(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshVertexAttributes rhs);
	MeshSample::MeshVertexAttributes operator^(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshVertexAttributes rhs);
	MeshSample::MeshVertexAttributes operator~(MeshSample::MeshVertexAttributes the);
	bool operator==(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshVertexAttributes rhs);
	bool operator!=(MeshSample::MeshVertexAttributes lhs, MeshSample::MeshVertexAttributes rhs);
}
