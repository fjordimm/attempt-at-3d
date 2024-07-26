
#include "AttemptAt3D/(Drawing)/Mesh.hpp"

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

	void Mesh::generateGlVaoAndBuffers(ShaderManager& shaderManager)
	{
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);
		
		glGenBuffers(1, &this->vbo);
		// glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		glGenBuffers(1, &this->ebo);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		shaderManager.doAttribs();

		this->updateGlBufferData();

		glBindVertexArray(0);
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

		glBindVertexArray(0);
	}

	void Mesh::draw(ShaderManager& shaderManager, Tran& tran)
	{
		if (this->meshData)
		{
			glBindVertexArray(this->vao);
			
			shaderManager.setUni_transScaleVal(tran.getScaleMatrix());
			shaderManager.setUni_transRotVal(tran.getRotationMatrix());
			shaderManager.setUni_transPosVal(tran.getPositionMatrix());
			glDrawElements(GL_TRIANGLES, this->meshData->elementsLen, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}
	}

	// TODO: optimize draw() by only binding the vao if the previously drawn vao wasn't the same one
}