
#pragma once

#include <memory>
#include <cstdlib>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AttemptAt3D
{
	class Mesh
	{
		/* Fields */

	   public:
		std::size_t verticesLen;
		std::unique_ptr<float[]> vertices;
		std::size_t elementsLen;
		std::unique_ptr<GLuint[]> elements;

		/* Constructors */

	   public:
		Mesh() = delete;
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		
		Mesh(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements);

		/* Methods */

		std::string toString() const;
	};
}
