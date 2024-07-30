
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/HasNormals.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	/* Constructors */

	HasNormals::HasNormals() :
		attribNormal(-1)
	{}

	/* Methods */

	void HasNormals::enableAttribsForMesh__()
	{
		glEnableVertexAttribArray(this->attribNormal);
		glVertexAttribPointer(this->attribNormal, 3, GL_FLOAT, GL_FALSE, this->getStride(), (void*)this->ThreeDShape::getStride());

		this->enableAttribsForMesh___();
	}

	GLsizei HasNormals::getStride__()
	{
		return 3 * sizeof(float) + this->getStride___();
	}

	void HasNormals::setupUniforms__()
	{
		this->setupUniforms___();
	}

	void HasNormals::setupAttributes__()
	{
		this->setupAttributes___();
	}

	void HasNormals::updateUniformsFromTran__(Tran& tran) const
	{
		this->updateUniformsFromTran___(tran);
	}
}