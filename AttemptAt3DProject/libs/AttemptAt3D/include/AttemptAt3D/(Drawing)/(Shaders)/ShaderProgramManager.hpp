
#pragma once

#include <vector>
#include <memory>
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderProgram.hpp"

namespace AttemptAt3D
{
	class ShaderProgramManager
	{
		/* Constructors */

	   public:
		ShaderProgramManager(const ShaderProgramManager&) = delete;
		ShaderProgramManager& operator=(const ShaderProgramManager&) = delete;
		
		ShaderProgramManager();
		
		/* Fields */

	   private:
		std::vector<std::unique_ptr<ShaderProgram>> shaderPrograms;

		float _fov;
		float _aspectRatio;
		float _nearClippingPlane;
		float _farClippingPlane;

		/* Getters and Setters */

	   public:
		void setFov(float val);
		void setAspectRatio(float val);
		void setNearClippingPlane(float val);
		void setFarClippingPlane(float val);

		/* Methods */

	   public:
		ShaderProgram* add(std::unique_ptr<ShaderProgram> shaderProgram);
		void drawEverything();
		void setViewMatrix(const glm::mat4& val);

	   private:
		void _updateProjectionMatrix();
	};
}
