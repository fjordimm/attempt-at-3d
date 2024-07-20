
#include "AttemptAt3D/(BodyManager)/_BodyManager/Body.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D::_BodyManager
{
	/* Constructors */

	Body::Body() :
		transform(glm::mat4(1.0f)),
		vao(-1),
		vbo(-1),
		ebo(-1),
		mesh(nullptr)
	{}

	/* Methods */

	void Body::setMesh(std::unique_ptr<Mesh> mesh)
	{
		this->mesh = std::move(mesh);
	}

	void Body::initializeVao(ShaderManager& shaderManager)
	{
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);
		
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		glGenBuffers(1, &this->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		glBufferData(GL_ARRAY_BUFFER, this->mesh->verticesLen * sizeof(this->mesh->vertices[0]), this->mesh->vertices.get(), GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mesh->elementsLen * sizeof(this->mesh->elements[0]), this->mesh->elements.get(), GL_DYNAMIC_DRAW);

		shaderManager.doAttribs();

		glBindVertexArray(0);
	}

	void Body::drawBody(ShaderManager& shaderManager)
	{
		glBindVertexArray(this->vao);

		shaderManager.set_uni_modelVal(this->transform);
		glDrawElements(GL_TRIANGLES, this->mesh->elementsLen, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void Body::cleanupForGl()
	{
		glDeleteBuffers(1, &this->ebo);
		glDeleteBuffers(1, &this->vbo);
		glDeleteVertexArrays(1, &this->vao);
	}
}
