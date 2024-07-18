
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AttemptAt3D::_BodyManager
{
	class Body
	{
	public:
		Body();
		~Body();
		Body(const Body&) = delete;
		Body& operator=(const Body&) = delete;

		GLuint get_vao() { return this->vao; }
		GLuint get_vbo() { return this->vbo; }
		GLuint get_ebo() { return this->ebo; }
	
	private:
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
	};
}
