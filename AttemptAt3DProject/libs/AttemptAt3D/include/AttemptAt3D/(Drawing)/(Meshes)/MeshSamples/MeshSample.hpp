
#pragma once

#include <memory>
#include <vector>
#include <cstdlib>
#include <type_traits>
#include <tuple>
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
		enum class MeshVertAttribs : std::uint32_t
		{
			None        = 0u,
			Positions3D = 1u << 0,
			Normals3D   = 1u << 1,

			PositionsAndNormals3D = Positions3D | Normals3D
		};

		/* Constructors */

	   public:
		MeshSample(const MeshSample&) = delete;
		MeshSample& operator=(const MeshSample&) = delete;

		MeshSample();

		/* Methods */

	   public:
		std::unique_ptr<MeshData> make(MeshVertAttribs attribs = MeshVertAttribs::Positions3D) const;

	   protected:
		virtual std::unique_ptr<const std::vector<Vec>> vertPositions3D() const = 0;
		virtual std::unique_ptr<const std::vector<Vec>> vertNormals3D() const = 0;
		virtual std::unique_ptr<const std::vector<std::tuple<GLuint, GLuint, GLuint>>> triangles() const = 0;
	};

	/* Enum Operator Overloads */

	MeshSample::MeshVertAttribs operator|(MeshSample::MeshVertAttribs lhs, MeshSample::MeshVertAttribs rhs);
	MeshSample::MeshVertAttribs operator&(MeshSample::MeshVertAttribs lhs, MeshSample::MeshVertAttribs rhs);
	MeshSample::MeshVertAttribs operator^(MeshSample::MeshVertAttribs lhs, MeshSample::MeshVertAttribs rhs);
	MeshSample::MeshVertAttribs operator~(MeshSample::MeshVertAttribs the);
	bool operator==(MeshSample::MeshVertAttribs lhs, MeshSample::MeshVertAttribs rhs);
	bool operator!=(MeshSample::MeshVertAttribs lhs, MeshSample::MeshVertAttribs rhs);
}
