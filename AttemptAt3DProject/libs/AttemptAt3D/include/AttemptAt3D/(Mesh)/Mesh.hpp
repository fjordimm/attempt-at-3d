
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <cstdlib>

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

		/* Getters and Setters */

	//    public:
	// 	inline std::size_t get_verticesLen() { return this->verticesLen; }
	// 	inline float* get_vertices() { return this->vertices.get(); }
	// 	inline std::size_t get_elementsLen() { return this->elementsLen; }
	// 	inline GLuint* get_elements() { return this->elements.get(); }

		/* Constructors */

	   public:
		Mesh() = delete;
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		
		Mesh(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements);

		/* Methods */
	};
}
