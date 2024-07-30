
#pragma once

#include <list>
#include <memory>
#include "AttemptAt3D/(InputManager)/InputManager.hpp"
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderProgramManager.hpp"
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

	   public:
		InputManager inputManager;
		ShaderProgramManager shaderProgramManager;
		MeshManager meshManager;
		std::list<std::unique_ptr<Form>> forms;

		bool hasCapturedCursorForCamera;
		std::unique_ptr<Forms::Camera> mainCamera;
		float mainCameraMovementSpeed;
		float mainCameraRotationSpeed;
	};
}
