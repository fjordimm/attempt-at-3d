
#include "AttemptAt3D/(Form)/Forms/Camera.hpp"

#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"

namespace AttemptAt3D::Forms
{
	/* Methods */

	void Camera::recalculateAndApplyViewMatrix(WorldState& worldState)
	{
		glm::mat4 viewMatrix = glm::lookAt(
			this->tran.getPosition(),
			this->tran.getPosition() + this->tran.getForwardVec(),
			this->tran.getUpVec()
		);

		worldState.shaderProgramManager.setViewMatrix(viewMatrix);
	}

	void Camera::onCreate__(WorldState& worldState)
	{
		this->velocity = Vecs::Zero;
		this->friction = 0.01f;

		this->onCreate___(worldState);
	}

	void Camera::onUpdate__(WorldState& worldState, float deltaTime)
	{
		this->tran.move(deltaTime * this->velocity);
		this->velocity *= 1.0f - this->friction * deltaTime;

		this->onUpdate___(worldState, deltaTime);
	}
}
