
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

namespace AttemptAt3D::_BodyManager
{
	class Body
	{
		/* Fields */

	   private:
		GLuint vao;
		GLuint vbo;
		GLuint ebo;

		std::size_t verticesLen;
		std::unique_ptr<float[]> vertices;
		std::size_t elementsLen;
		std::unique_ptr<GLuint[]> elements;

		/* Getters and Setters */

	   public:
		inline std::size_t get_verticesLen() { return this->verticesLen; }
		inline const float* get_vertices() { return this->vertices.get(); }
		inline std::size_t get_elementsLen() { return this->elementsLen; }
		inline const GLuint* get_elements() { return this->elements.get(); }

		/* Constructors */

	   public:
		Body(const Body&) = delete;
		Body& operator=(const Body&) = delete;
		// Body(Body&&) {}
		
		Body();

		/* Methods */

	   public:
		void setData(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements);
		void doGens();
		void bindAndAttachData();
		void cleanupForGl();
	};
}
