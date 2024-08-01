
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderProgramManager.hpp"

#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/InSpace.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	ShaderProgramManager::ShaderProgramManager() :
		shaderPrograms(),
		_mayHaveChangedProjectionMatrix(true),
		_fov(Math::PiOver4),
		_aspectRatio(1.0f),
		_nearClippingPlane(0.01f),
		_farClippingPlane(100000.0f),
		_mayHaveChangedSunRotMatrix(true),
		_sunRot(Quats::Identity),
		_mayHaveChangedSunlight(true),
		_sunBrightness(1.0f),
		_sunAmbientLight(0.0f),
		_sunColor(Colors::White)
	{}

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
		bool madeNewProjectionMatrix = false;
		if (this->_mayHaveChangedProjectionMatrix)
		{
			this->_updateProjectionMatrix();
			madeNewProjectionMatrix = true;
			this->_mayHaveChangedProjectionMatrix = false;
		}

		bool madeNewSunRotMatrix = false;
		if (this->_mayHaveChangedSunRotMatrix)
		{
			this->_updateSunRotMatrix();
			madeNewSunRotMatrix = true;
			this->_mayHaveChangedSunRotMatrix = false;
		}

		bool madeNewSunlight = false;
		if (this->_mayHaveChangedSunlight)
		{
			madeNewSunlight = true;
			this->_mayHaveChangedSunlight = false;
		}

		for (std::unique_ptr<ShaderProgram>& shaderProgram_ : this->shaderPrograms)
		{
			ShaderProgram* shaderProgram = shaderProgram_.get();

			shaderProgram->use();
			
			ShaderPrograms::InSpace* inSpaceShaderProgram = dynamic_cast<ShaderPrograms::InSpace*>(shaderProgram);
			if (inSpaceShaderProgram != nullptr)
			{
				if (madeNewProjectionMatrix)
				{
					inSpaceShaderProgram->setUniProj(this->_cached_projectionMatrix);
				}

				if (madeNewSunRotMatrix)
				{
					inSpaceShaderProgram->setUniSunRot(this->_cached_sunRotMatrix);
				}

				if (madeNewSunlight)
				{
					inSpaceShaderProgram->setUniSunBrightness(this->_sunBrightness);
					inSpaceShaderProgram->setUniSunAmbientLight(this->_sunAmbientLight);
					inSpaceShaderProgram->setUniSunColor(this->_sunColor.toVec());
				}
			}

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
				inSpaceShaderProgram->use();
				inSpaceShaderProgram->setUniView(val);
			}
		}
	}

	void ShaderProgramManager::_updateProjectionMatrix()
	{
		this->_cached_projectionMatrix = glm::perspective(this->_fov, this->_aspectRatio, this->_nearClippingPlane, this->_farClippingPlane);
	}

	void ShaderProgramManager::_updateSunRotMatrix()
	{
		this->_cached_sunRotMatrix = glm::mat4_cast(this->_sunRot);
	}
}
