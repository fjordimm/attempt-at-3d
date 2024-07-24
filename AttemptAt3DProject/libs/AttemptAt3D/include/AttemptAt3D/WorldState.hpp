
#pragma once

#include <list>
#include <memory>
#include "AttemptAt3D/(ShaderManager)/ShaderManager.hpp"
#include "AttemptAt3D/(InputManager)/InputManager.hpp"
#include "AttemptAt3D/(Form)/Form.hpp"
#include "AttemptAt3D/(Form)/Forms/Camera.hpp"

namespace AttemptAt3D
{
	/* Forward Declarations */

	// class Form;
	// namespace Forms { class Camera; }

	class WorldState
	{
		/* Constructors */

	   public:
		WorldState(const WorldState&) = delete;
		WorldState& operator=(const WorldState&) = delete;
		
		WorldState();
		
		/* Fields */

	   private:
		float _fov;
		float _aspectRatio;
		float _nearClippingPlane;
		float _farClippingPlane;

	   public:
		ShaderManager shaderManager;
		InputManager inputManager;
		std::list<std::unique_ptr<Form>> forms;

		bool hasCapturedCursorForCamera;
		std::unique_ptr<Forms::Camera> mainCamera;
		float mainCameraMovementSpeed;
		float mainCameraRotationSpeed;

		/* Getters and Setters */

	   public:
		void setFov(float val);
		void setAspectRatio(float val);
		void setNearClippingPlane(float val);
		void setFarClippingPlane(float val);

		/* Methods */

	   private:
		void _updateProjectionMatrix();
	};
}
