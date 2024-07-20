
#include "AttemptAt3D/BodyManager/_BodyManager/Body.hpp"

#include "AttemptAt3D/Debug/Debug.hpp"

namespace AttemptAt3D::_BodyManager
{
	/* Constructors */

	Body::Body() :
		vao(-1),
		vbo(-1),
		ebo(-1),
		verticesLen(0),
		vertices(nullptr),
		elementsLen(0),
		elements(nullptr)
	{}

	/* Methods */

	void Body::setData(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements)
	{
		this->verticesLen = verticesLen;
		this->vertices = std::move(vertices);
		this->elementsLen = elementsLen;
		this->elements = std::move(elements);
	}

	void Body::initializeVao(ShaderManager& shaderManager)
	{
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);
		
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		glGenBuffers(1, &this->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		glBufferData(GL_ARRAY_BUFFER, this->verticesLen * sizeof(this->vertices[0]), this->vertices.get(), GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elementsLen * sizeof(this->elements[0]), this->elements.get(), GL_DYNAMIC_DRAW);

		shaderManager.doAttribs();

		glBindVertexArray(0);
	}

	void Body::drawBody()
	{
		glBindVertexArray(this->vao);

		glDrawElements(GL_TRIANGLES, this->elementsLen, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void Body::cleanupForGl()
	{
		glDeleteBuffers(1, &this->ebo);
		glDeleteBuffers(1, &this->vbo);
		glDeleteVertexArrays(1, &this->vao);
	}
}
