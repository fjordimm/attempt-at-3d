
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderProgramManager.hpp"

#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/InSpace.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	ShaderProgramManager::ShaderProgramManager() :
		shaderPrograms()
	{}

	/* Getters and Setters */

	void ShaderProgramManager::setFov(float val)
	{
		this->_fov = val;
		this->_updateProjectionMatrix();
	}

	void ShaderProgramManager::setAspectRatio(float val)
	{
		this->_aspectRatio = val;
		this->_updateProjectionMatrix();
	}

	void ShaderProgramManager::setNearClippingPlane(float val)
	{
		this->_nearClippingPlane = val;
		this->_updateProjectionMatrix();
	}

	void ShaderProgramManager::setFarClippingPlane(float val)
	{
		this->_farClippingPlane = val;
		this->_updateProjectionMatrix();
	}

	/* Methods */

	ShaderProgram* ShaderProgramManager::add(std::unique_ptr<ShaderProgram> shaderProgram)
	{
		ShaderProgram* ret = shaderProgram.get();
		ret->compileAndActivate();
		this->shaderPrograms.push_back(std::move(shaderProgram));

		this->_updateProjectionMatrix();

		return ret;
	}

	void ShaderProgramManager::drawEverything()
	{
		for (std::unique_ptr<ShaderProgram>& shaderProgram_ : this->shaderPrograms)
		{
			ShaderProgram* shaderProgram = shaderProgram_.get();

			shaderProgram->drawAllTrans();
		}
	}

	void ShaderProgramManager::setViewMatrix(const glm::mat4& val)
	{
		for (std::unique_ptr<ShaderProgram>& shaderProgram_ : this->shaderPrograms)
		{
			ShaderProgram* shaderProgram = shaderProgram_.get();

			ShaderPrograms::InSpace* inSpaceShaderProgram = dynamic_cast<ShaderPrograms::InSpace*>(shaderProgram);
			if (inSpaceShaderProgram != nullptr)
			{
				inSpaceShaderProgram->setUniView(val);
			}
		}
	}

	void ShaderProgramManager::_updateProjectionMatrix()
	{
		glm::mat4 projMat = glm::perspective(this->_fov, this->_aspectRatio, this->_nearClippingPlane, this->_farClippingPlane);

		for (std::unique_ptr<ShaderProgram>& shaderProgram_ : this->shaderPrograms)
		{
			ShaderProgram* shaderProgram = shaderProgram_.get();

			ShaderPrograms::InSpace* inSpaceShaderProgram = dynamic_cast<ShaderPrograms::InSpace*>(shaderProgram);
			if (inSpaceShaderProgram != nullptr)
			{
				inSpaceShaderProgram->setUniProj(projMat);
			}
		}
	}
}
