
#include "AttemptAt3D/BodyManager/Body.h"

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

	void Body::doGens()
	{
		glGenVertexArrays(1, &this->vao);
		glGenBuffers(1, &this->vbo);
		glGenBuffers(1, &this->ebo);
	}

	void Body::setData(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements)
	{
		this->verticesLen = verticesLen;
		this->vertices = std::move(vertices);
		this->elementsLen = elementsLen;
		this->elements = std::move(elements);
	}

	void Body::bindAndAttachData()
	{
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		glBufferData(GL_ARRAY_BUFFER, this->verticesLen * sizeof(this->vertices[0]), this->vertices.get(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elementsLen * sizeof(this->elements[0]), this->elements.get(), GL_STATIC_DRAW);
	}
}
