
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshVertAttribs.hpp"

#include <type_traits>

namespace AttemptAt3D
{
	MeshVertAttribs operator|(MeshVertAttribs lhs, MeshVertAttribs rhs)
	{
		return static_cast<MeshVertAttribs>(
			static_cast<std::underlying_type_t<MeshVertAttribs>>(lhs) |
			static_cast<std::underlying_type_t<MeshVertAttribs>>(rhs)
		);
	}

	MeshVertAttribs operator&(MeshVertAttribs lhs, MeshVertAttribs rhs)
	{
		return static_cast<MeshVertAttribs>(
			static_cast<std::underlying_type_t<MeshVertAttribs>>(lhs) &
			static_cast<std::underlying_type_t<MeshVertAttribs>>(rhs)
		);
	}

	MeshVertAttribs operator^(MeshVertAttribs lhs, MeshVertAttribs rhs)
	{
		return static_cast<MeshVertAttribs>(
			static_cast<std::underlying_type_t<MeshVertAttribs>>(lhs) ^
			static_cast<std::underlying_type_t<MeshVertAttribs>>(rhs)
		);
	}

	MeshVertAttribs operator~(MeshVertAttribs the)
	{
		return static_cast<MeshVertAttribs>(
			~static_cast<std::underlying_type_t<MeshVertAttribs>>(the)
		);
	}

	bool operator==(MeshVertAttribs lhs, MeshVertAttribs rhs)
	{
		return
			static_cast<std::underlying_type_t<MeshVertAttribs>>(lhs) ==
			static_cast<std::underlying_type_t<MeshVertAttribs>>(rhs);
	}

	bool operator!=(MeshVertAttribs lhs, MeshVertAttribs rhs)
	{
		return
			static_cast<std::underlying_type_t<MeshVertAttribs>>(lhs) !=
			static_cast<std::underlying_type_t<MeshVertAttribs>>(rhs);
	}
}
