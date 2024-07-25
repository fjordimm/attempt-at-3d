
#include "AttemptAt3D/WorldState.hpp"
#include "AttemptAt3D/(Form)/Form.hpp"
#include "AttemptAt3D/(Form)/Forms/Camera.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	WorldState::WorldState() :
		shaderManager(),
		inputManager(),
		forms(),
		hasCapturedCursorForCamera(false),
		mainCamera(nullptr),
		mainCameraMovementSpeed(0.008f),
		mainCameraRotationSpeed(0.0025f)
	{}

	/* Getters and Setters */

	void WorldState::setFov(float val)
	{
		this->_fov = val;
		this->_updateProjectionMatrix();
	}

	void WorldState::setAspectRatio(float val)
	{
		this->_aspectRatio = val;
		this->_updateProjectionMatrix();
	}

	void WorldState::setNearClippingPlane(float val)
	{
		this->_nearClippingPlane = val;
		this->_updateProjectionMatrix();
	}

	void WorldState::setFarClippingPlane(float val)
	{
		this->_farClippingPlane = val;
		this->_updateProjectionMatrix();
	}

	/* Methods */

	void WorldState::_updateProjectionMatrix()
	{
		this->shaderManager.setUni_projVal(
			glm::perspective(this->_fov, this->_aspectRatio, this->_nearClippingPlane, this->_farClippingPlane)
		);
	}
}
