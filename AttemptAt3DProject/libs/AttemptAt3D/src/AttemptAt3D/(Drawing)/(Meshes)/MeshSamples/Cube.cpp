
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/Cube.hpp"

namespace AttemptAt3D::MeshSamples
{
	std::unique_ptr<const std::vector<Vec>> Cube::vertPositions3D() const
	{
		std::unique_ptr<std::vector<Vec>> ret(new std::vector<Vec>{
			Vec(-1.0f, +1.0f, -1.0f),
			Vec(+1.0f, +1.0f, -1.0f),
			Vec(-1.0f, -1.0f, -1.0f),
			Vec(+1.0f, -1.0f, -1.0f),
			Vec(-1.0f, +1.0f, +1.0f),
			Vec(+1.0f, +1.0f, +1.0f),
			Vec(-1.0f, -1.0f, +1.0f),
			Vec(+1.0f, -1.0f, +1.0f)
		});

		return std::move(ret);
	}

	std::unique_ptr<const std::vector<Vec>> Cube::vertNormals3D() const
	{
		std::unique_ptr<std::vector<Vec>> ret(new std::vector<Vec>{
			glm::normalize(Vec(-1.0f, +1.0f, -1.0f)),
			glm::normalize(Vec(+1.0f, +1.0f, -1.0f)),
			glm::normalize(Vec(-1.0f, -1.0f, -1.0f)),
			glm::normalize(Vec(+1.0f, -1.0f, -1.0f)),
			glm::normalize(Vec(-1.0f, +1.0f, +1.0f)),
			glm::normalize(Vec(+1.0f, +1.0f, +1.0f)),
			glm::normalize(Vec(-1.0f, -1.0f, +1.0f)),
			glm::normalize(Vec(+1.0f, -1.0f, +1.0f))
		});

		return std::move(ret);
	}

	std::unique_ptr<const std::vector<std::tuple<GLuint, GLuint, GLuint>>> Cube::triangles() const
	{
		std::unique_ptr<std::vector<std::tuple<GLuint, GLuint, GLuint>>> ret(new std::vector<std::tuple<GLuint, GLuint, GLuint>>{
			// bottom
			std::make_tuple<GLuint, GLuint, GLuint>(0, 3, 2),
			std::make_tuple<GLuint, GLuint, GLuint>(3, 0, 1),

			// top
			std::make_tuple<GLuint, GLuint, GLuint>(6, 5, 4),
			std::make_tuple<GLuint, GLuint, GLuint>(5, 6, 7),

			// front
			std::make_tuple<GLuint, GLuint, GLuint>(2, 7, 6),
			std::make_tuple<GLuint, GLuint, GLuint>(7, 2, 3),

			// back
			std::make_tuple<GLuint, GLuint, GLuint>(1, 4, 5),
			std::make_tuple<GLuint, GLuint, GLuint>(4, 1, 0),

			// left
			std::make_tuple<GLuint, GLuint, GLuint>(0, 6, 4),
			std::make_tuple<GLuint, GLuint, GLuint>(6, 0, 2),

			// right
			std::make_tuple<GLuint, GLuint, GLuint>(3, 5, 7),
			std::make_tuple<GLuint, GLuint, GLuint>(5, 3, 1)
		});

		return std::move(ret);
	}
}
