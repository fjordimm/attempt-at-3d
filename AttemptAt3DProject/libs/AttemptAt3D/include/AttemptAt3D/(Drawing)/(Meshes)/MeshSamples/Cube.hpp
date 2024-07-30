
#pragma once

#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/MeshSample.hpp"

namespace AttemptAt3D::MeshSamples
{
	class Cube : public MeshSample
	{
	   protected:
		std::unique_ptr<const std::vector<Vec>> vertPositions3D() const final;
		std::unique_ptr<const std::vector<Vec>> vertNormals3D() const final;
		std::unique_ptr<const std::vector<std::tuple<GLuint, GLuint, GLuint>>> triangles() const final;
	};
}
