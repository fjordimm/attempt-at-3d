
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
	public:
		Body();
		~Body();
		Body(const Body&) = delete;
		Body& operator=(const Body&) = delete;
		Body(Body&&) {}

		void doGens();
		void setData(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements);
		void bindAndAttachData();

		std::size_t get_verticesLen() { return this->verticesLen; }
		const float* get_vertices() { return this->vertices.get(); }
		std::size_t get_elementsLen() { return this->elementsLen; }
		const GLuint* get_elements() { return this->elements.get(); }

		// GLuint get_vao() { return this->vao; }
		// GLuint get_vbo() { return this->vbo; }
		// GLuint get_ebo() { return this->ebo; }
	
	private:
		GLuint vao;
		GLuint vbo;
		GLuint ebo;

		std::size_t verticesLen;
		std::unique_ptr<float[]> vertices;
		std::size_t elementsLen;
		std::unique_ptr<GLuint[]> elements;
	};
}
