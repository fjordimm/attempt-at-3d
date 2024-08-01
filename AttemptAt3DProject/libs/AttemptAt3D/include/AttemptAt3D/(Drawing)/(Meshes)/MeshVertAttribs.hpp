
#pragma once

#include <cstdint>

namespace AttemptAt3D
{
	enum class MeshVertAttribs : std::uint32_t
	{
		None        = 0u,
		Positions3D = 1u << 0,
		Normals3D   = 1u << 1
	};

	MeshVertAttribs operator|(MeshVertAttribs lhs, MeshVertAttribs rhs);
	MeshVertAttribs operator&(MeshVertAttribs lhs, MeshVertAttribs rhs);
	MeshVertAttribs operator^(MeshVertAttribs lhs, MeshVertAttribs rhs);
	MeshVertAttribs operator~(MeshVertAttribs the);
	bool operator==(MeshVertAttribs lhs, MeshVertAttribs rhs);
	bool operator!=(MeshVertAttribs lhs, MeshVertAttribs rhs);
}
