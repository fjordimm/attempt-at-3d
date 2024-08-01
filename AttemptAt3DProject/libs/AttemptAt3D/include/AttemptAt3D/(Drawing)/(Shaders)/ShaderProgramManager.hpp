
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

		bool _mayHaveChangedProjectionMatrix;
		float _fov;
		float _aspectRatio;
		float _nearClippingPlane;
		float _farClippingPlane;
		glm::mat4 _cached_projectionMatrix;

		bool _mayHaveChangedSunRotMatrix;
		Quat _sunRot;
		glm::mat4 _cached_sunRotMatrix;

		bool _mayHaveChangedSunlight;
		float _sunBrightness;
		float _sunAmbientLight;
		Color _sunColor;

		/* Getters and Setters */

	   public:
		inline const float& getFov() const { return this->_fov; }
		inline const float& getAspectRatio() const { return this->_aspectRatio; }
		inline const float& getNearClippingPlane() const { return this->_nearClippingPlane; }
		inline const float& getFarClippingPlane() const { return this->_farClippingPlane; }
		inline float& acqFov() { this->_mayHaveChangedProjectionMatrix = true; return this->_fov; }
		inline float& acqAspectRatio() { this->_mayHaveChangedProjectionMatrix = true; return this->_aspectRatio; }
		inline float& acqNearClippingPlane() { this->_mayHaveChangedProjectionMatrix = true; return this->_nearClippingPlane; }
		inline float& acqFarClippingPlane() { this->_mayHaveChangedProjectionMatrix = true; return this->_farClippingPlane; }

		inline const Quat& getSunRot() const { return this->_sunRot; }
		inline Quat& acqSunRot() { this->_mayHaveChangedSunRotMatrix = true; return this->_sunRot; }

		inline const float& getSunBrightness() const { return this->_sunBrightness; }
		inline const float& getSunAmbientLight() const { return this->_sunAmbientLight; }
		inline const Color& getSunColor() const { return this->_sunColor; }
		inline float& acqSunBrightness() { this->_mayHaveChangedSunlight = true; return this->_sunBrightness; }
		inline float& acqSunAmbientLight() { this->_mayHaveChangedSunlight = true; return this->_sunAmbientLight; }
		inline Color& acqSunColor() { this->_mayHaveChangedSunlight = true; return this->_sunColor; }

		/* Methods */

	   public:
		ShaderProgram* add(std::unique_ptr<ShaderProgram> shaderProgram);
		void drawEverything();
		void setViewMatrix(const glm::mat4& val);

	   private:
		void _updateProjectionMatrix();
		void _updateSunRotMatrix();
	};
}
