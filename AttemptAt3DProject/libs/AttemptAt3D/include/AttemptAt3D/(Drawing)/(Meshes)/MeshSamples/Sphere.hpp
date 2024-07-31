
#pragma once

#include <cstdlib>
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/MeshSample.hpp"

namespace AttemptAt3D::MeshSamples
{
	template <std::size_t Size>
	class Sphere : public MeshSample
	{
	   protected:
		std::unique_ptr<std::vector<Vec>> vertPositions3D() const final;
		std::unique_ptr<std::vector<Vec>> vertNormals3D() const final;
		std::unique_ptr<std::vector<std::tuple<GLuint, GLuint, GLuint>>> triangles() const final;
	};
}
