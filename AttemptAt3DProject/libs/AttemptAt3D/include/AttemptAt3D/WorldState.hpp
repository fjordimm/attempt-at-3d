
#pragma once

#include <list>
#include <memory>
#include "AttemptAt3D/(InputManager)/InputManager.hpp"
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(NonAbstract)/Flat.hpp"
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshManager.hpp"

namespace AttemptAt3D
{
	/* Forward Declarations */

	class Form;
	namespace Forms { class Camera; }

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
		InputManager inputManager;
		ShaderPrograms::Flat shaderProgram_flat;
		MeshManager meshManager;
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
