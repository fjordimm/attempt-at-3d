
#include "AttemptAt3D/(DrawObj)/DrawObj.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	DrawObj::DrawObj(ShaderManager& shaderManager, Tran* tran, Mesh* mesh) :
		tran(tran),
		mesh(mesh),
		vao(-1),
		vbo(-1),
		ebo(-1)
	{
		if (this->mesh)
		{
			/* Initialize VAO */

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
	}

	/* Methods */

	void DrawObj::draw(ShaderManager& shaderManager) const
	{
		if (this->mesh)
		{
			glBindVertexArray(this->vao);
			
			shaderManager.setUni_transScaleVal(this->tran->getScaleMatrix());
			shaderManager.setUni_transRotVal(this->tran->getRotationMatrix());
			shaderManager.setUni_transPosVal(this->tran->getPositionMatrix());
			glDrawElements(GL_TRIANGLES, this->mesh->elementsLen, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}
	}

	void DrawObj::cleanupForGl()
	{
		// glDeleteBuffers(1, &this->ebo);
		// glDeleteBuffers(1, &this->vbo);
		// glDeleteVertexArrays(1, &this->vao);
	}
}
