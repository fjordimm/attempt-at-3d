
#pragma once

#include <memory>
#include <cstdlib>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AttemptAt3D
{
	class MeshData
	{
		/* Constructors */

	   public:
		MeshData() = delete;
		MeshData(const MeshData&) = delete;
		MeshData& operator=(const MeshData&) = delete;
		
		MeshData(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements);

		/* Fields */

	   public:
		std::size_t verticesLen;
		std::unique_ptr<float[]> vertices;
		std::size_t elementsLen;
		std::unique_ptr<GLuint[]> elements;

		/* Methods */

		std::string toString() const;
	};
}
