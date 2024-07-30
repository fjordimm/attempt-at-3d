
#include "AttemptAt3D/WorldState.hpp"

#include "AttemptAt3D/(Form)/Form.hpp"
#include "AttemptAt3D/(Form)/Forms/Camera.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	WorldState::WorldState() :
		inputManager(),
		shaderProgramManager(),
		meshManager(),
		forms(),
		hasCapturedCursorForCamera(false),
		mainCamera(nullptr),
		mainCameraMovementSpeed(0.008f),
		mainCameraRotationSpeed(0.0025f)
	{}
}
