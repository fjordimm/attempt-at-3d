
#pragma once

#include <vector>
#include <memory>
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderProgram.hpp"
#include "AttemptAt3D/(Util)/(Color)/Color.hpp"

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

		float _sunBrightness;
		float _sunAmbientLight;
		Color _sunColor;

		/* Getters and Setters */

	   public:
		void setFov(float val);
		void setAspectRatio(float val);
		void setNearClippingPlane(float val);
		void setFarClippingPlane(float val);

		void setSunBrightness(float val);
		void setSunAmbientLight(float val);
		void setSunColor(Color val);

		/* Methods */

	   public:
		ShaderProgram* add(std::unique_ptr<ShaderProgram> shaderProgram);
		void drawEverything();
		void setViewMatrix(const glm::mat4& val);
		void setSunRotMatrix(const glm::mat4& val);

		// TODO: optimize _updateProjectionMatrix() and the setters for the sun uniforms so they only do stuff once per frame instead of on every call

	   private:
		void _updateProjectionMatrix();
	};
}
