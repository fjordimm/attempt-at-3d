
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

	// static constexpr float VERTICES[] =
	// {
	// 	// X      Y      Z
	// 	 -1.0f, +1.0f, -1.0f,
	// 	 +1.0f, +1.0f, -1.0f,
	// 	 -1.0f, -1.0f, -1.0f,
	// 	 +1.0f, -1.0f, -1.0f,
		 
	// 	 -1.0f, +1.0f, +1.0f,
	// 	 +1.0f, +1.0f, +1.0f,
	// 	 -1.0f, -1.0f, +1.0f,
	// 	 +1.0f, -1.0f, +1.0f,
	// };

	// static constexpr GLuint ELEMENTS[] =
	// {
	// 	// bottom
	// 	0, 3, 2,
	// 	3, 0, 1,

	// 	// top
	// 	6, 5, 4,
	// 	5, 6, 7,

	// 	// front
	// 	2, 7, 6,
	// 	7, 2, 3,

	// 	// back
	// 	1, 4, 5,
	// 	4, 1, 0,

	// 	// left
	// 	0, 6, 4,
	// 	6, 0, 2,

	// 	// right
	// 	3, 5, 7,
	// 	5, 3, 1
	// };
	
	// std::size_t Cube::verticesSize() const
	// { return sizeof(VERTICES); }

	// const float* Cube::vertices() const
	// { return VERTICES; }

	// std::size_t Cube::elementsSize() const
	// { return sizeof(ELEMENTS); }

	// const GLuint* Cube::elements() const
	// { return ELEMENTS; }
}
