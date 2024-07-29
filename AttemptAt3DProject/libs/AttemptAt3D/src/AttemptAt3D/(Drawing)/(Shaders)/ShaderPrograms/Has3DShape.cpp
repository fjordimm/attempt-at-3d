
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/Has3DShape.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	/* Constructors */

	Has3DShape::Has3DShape() : 
		uniTransScale(-1),
		uniTransRot(-1),
		uniTransPos(-1)
	{}

	/* Getters & Setters */

	void Has3DShape::setUniTransScale(const glm::mat4& val) const
	{ glUniformMatrix4fv(this->uniTransScale, 1, GL_FALSE, glm::value_ptr(val)); }

	void Has3DShape::setUniTransRot(const glm::mat4& val) const
	{ glUniformMatrix4fv(this->uniTransRot, 1, GL_FALSE, glm::value_ptr(val)); }

	void Has3DShape::setUniTransPos(const glm::mat4& val) const
	{ glUniformMatrix4fv(this->uniTransPos, 1, GL_FALSE, glm::value_ptr(val)); }

	/* Methods */

	void Has3DShape::enableAttribsForMesh_()
	{
		this->enableAttribsForMesh__();
	}

	void Has3DShape::setupUniforms_()
	{
		this->uniTransScale = glGetUniformLocation(this->program, "uni_transScale");
		glm::mat4 uniTransScale_val = glm::mat4(1.0f);
		glUniformMatrix4fv(this->uniTransScale, 1, GL_FALSE, glm::value_ptr(uniTransScale_val));

		this->uniTransRot = glGetUniformLocation(this->program, "uni_transRot");
		glm::mat4 uniTransRot_val = glm::mat4(1.0f);
		glUniformMatrix4fv(this->uniTransRot, 1, GL_FALSE, glm::value_ptr(uniTransRot_val));
		
		this->uniTransPos = glGetUniformLocation(this->program, "uni_transPos");
		glm::mat4 uniTransPos_val = glm::mat4(1.0f);
		glUniformMatrix4fv(this->uniTransPos, 1, GL_FALSE, glm::value_ptr(uniTransPos_val));

		this->setupUniforms__();
	}

	void Has3DShape::setupAttributes_()
	{
		this->setupAttributes__();
	}

	void Has3DShape::updateUniformsFromTran_(Tran& tran) const
	{
		this->setUniTransScale(tran.getScaleMatrix());
		this->setUniTransRot(tran.getRotationMatrix());
		this->setUniTransPos(tran.getPositionMatrix());

		this->updateUniformsFromTran__(tran);
	}
}
