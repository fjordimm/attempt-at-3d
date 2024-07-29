
#include "AttemptAt3D/(Drawing)/(Meshes)/Mesh.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Mesh::Mesh(std::unique_ptr<MeshData> meshData) :
		meshData(std::move(meshData)),
		vao(-1),
		vbo(-1),
		ebo(-1)
	{}

	/* Methods */

	void Mesh::generateGlVaoAndBuffers()
	{
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);
		
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		glGenBuffers(1, &this->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		// Immediately after the call of this function,
		//   someone must call ShaderProgram.enableAttribsForMesh(),
		//   and they must call Mesh.updateGlBufferData()

		// shaderManager.doAttribs();

		// this->updateGlBufferData();
	}

	void Mesh::cleanupForGl()
	{
		glDeleteBuffers(1, &this->ebo);
		glDeleteBuffers(1, &this->vbo);
		glDeleteVertexArrays(1, &this->vao);
	}

	void Mesh::updateGlBufferData()
	{
		glBindVertexArray(this->vao);

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		glBufferData(GL_ARRAY_BUFFER, this->meshData->verticesLen * sizeof(this->meshData->vertices[0]), this->meshData->vertices.get(), GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->meshData->elementsLen * sizeof(this->meshData->elements[0]), this->meshData->elements.get(), GL_DYNAMIC_DRAW);
	}

	GLuint Mesh::getVaoForDrawing()
	{
		return this->vao;
	}

	// TODO: optimize draw() by only binding the vao if the previously drawn vao wasn't the same one
}
