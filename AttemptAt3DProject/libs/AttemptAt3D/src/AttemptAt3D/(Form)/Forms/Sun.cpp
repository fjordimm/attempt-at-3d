
#include "AttemptAt3D/(Form)/Forms/Sun.hpp"

#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"

namespace AttemptAt3D::Forms
{
	/* Methods */

	void Sun::recalculateAndApplyViewMatrix(WorldState& worldState)
	{
		glm::mat4 viewMatrix = glm::lookAt(
			this->tran.getPosition(),
			this->tran.getPosition() + this->tran.getForwardVec(),
			this->tran.getUpVec()
		);

		worldState.shaderProgramManager.setViewMatrix(viewMatrix);
	}

	void Sun::onCreate_(WorldState& worldState)
	{
		this->onCreate__(worldState);
	}

	void Sun::onUpdate_(WorldState& worldState, float deltaTime)
	{
		this->onUpdate__(worldState, deltaTime);
	}
}
