
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/InSpace.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	/* Constructors */

	InSpace::InSpace() : 
		attribPosition(-1),
		attribColor(-1),
		uniView(-1),
		uniProj(-1),
		uniSunRot(-1)
	{}

	/* Getters & Setters */

	void InSpace::setUniView(const glm::mat4& val) const
	{ glUniformMatrix4fv(this->uniView, 1, GL_FALSE, glm::value_ptr(val)); }

	void InSpace::setUniProj(const glm::mat4& val) const
	{ glUniformMatrix4fv(this->uniProj, 1, GL_FALSE, glm::value_ptr(val)); }

	void InSpace::setUniSunRot(const glm::mat4& val) const
	{ glUniformMatrix4fv(this->uniSunRot, 1, GL_FALSE, glm::value_ptr(val)); }

	/* Methods */

	void InSpace::enableAttribsForMesh()
	{
		glEnableVertexAttribArray(this->attribPosition);
		glVertexAttribPointer(this->attribPosition, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

		glEnableVertexAttribArray(this->attribColor);
		glVertexAttribPointer(this->attribColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		this->enableAttribsForMesh_();
	}

	void InSpace::setupUniforms()
	{
		this->uniView = glGetUniformLocation(this->program, "uni_view");
		glm::mat4 uniView_val = glm::lookAt(
			glm::vec3(0.0f, -15.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		glUniformMatrix4fv(this->uniView, 1, GL_FALSE, glm::value_ptr(uniView_val));

		this->uniProj = glGetUniformLocation(this->program, "uni_proj");
		glm::mat4 uniProj_val = glm::perspective(glm::radians(45.0f), 1.0f /*aspect ratio*/, 1.0f, 100000.0f);
		glUniformMatrix4fv(this->uniProj, 1, GL_FALSE, glm::value_ptr(uniProj_val));

		this->uniSunRot = glGetUniformLocation(this->program, "uni_sunRot");
		glm::mat4 uniSunRot_val;
		{
			glm::quat quatX = glm::angleAxis(glm::radians(13.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotX = glm::toMat4(quatX);
			glm::quat quatY = glm::angleAxis(glm::radians(31.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotY = glm::toMat4(quatY);
			uniSunRot_val = rotY * rotX;
		}
		glUniformMatrix4fv(this->uniSunRot, 1, GL_FALSE, glm::value_ptr(uniSunRot_val));

		this->setupUniforms_();
	}

	void InSpace::setupAttributes()
	{
		this->attribPosition = glGetAttribLocation(this->program, "attrib_position");
		this->attribColor = glGetAttribLocation(this->program, "attrib_color");

		this->setupAttributes_();
	}

	void InSpace::updateUniformsFromTran(Tran& tran) const
	{
		this->updateUniformsFromTran_(tran);
	}
}
