
#include "AttemptAt3D/BodyManager/Body.hpp"

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

	void Body::doGlGens(ShaderManager& shaderManager)
	{
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);
		
		glGenBuffers(1, &this->vbo);
		glGenBuffers(1, &this->ebo);

		Debug::Printf("Names: {%u, %u, %u}\n", this->vao, this->vbo, this->ebo);

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		glBufferData(GL_ARRAY_BUFFER, this->verticesLen * sizeof(this->vertices[0]), this->vertices.get(), GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elementsLen * sizeof(this->elements[0]), this->elements.get(), GL_DYNAMIC_DRAW);

		shaderManager.doVertexAttribPointers();

		glBindVertexArray(0);
	}

	void Body::attachDataToGlBuffers()
	{
		// glBindVertexArray(this->vao);
		// glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		// glBufferData(GL_ARRAY_BUFFER, this->verticesLen * sizeof(this->vertices[0]), this->vertices.get(), GL_DYNAMIC_DRAW);
		// glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elementsLen * sizeof(this->elements[0]), this->elements.get(), GL_DYNAMIC_DRAW);

		// glNamedBufferData(this->vbo, this->verticesLen * sizeof(this->vertices[0]), this->vertices.get(), GL_STATIC_DRAW);
		// glNamedBufferData(this->ebo, this->elementsLen * sizeof(this->elements[0]), this->elements.get(), GL_STATIC_DRAW);
	}

	void Body::drawBody(ShaderManager& shaderManager)
	{
		glBindVertexArray(this->vao);
		// glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		// glBufferData(GL_ARRAY_BUFFER, this->verticesLen * sizeof(this->vertices[0]), this->vertices.get(), GL_DYNAMIC_DRAW);
		// glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elementsLen * sizeof(this->elements[0]), this->elements.get(), GL_DYNAMIC_DRAW);

		// shaderManager.doVertexAttribPointers();

		glDrawElements(GL_TRIANGLES, this->elementsLen, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, this->verticesLen);

		glBindVertexArray(0);
	}

	void Body::cleanupForGl()
	{
		glDeleteBuffers(1, &this->ebo);
		glDeleteBuffers(1, &this->vbo);
		glDeleteVertexArrays(1, &this->vao);
	}
}
