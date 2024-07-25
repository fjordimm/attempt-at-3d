
#include "AttemptAt3D/(Form)/PhysicForm.hpp"

namespace AttemptAt3D
{
	/* Methods */

	void PhysicForm::onCreate_(WorldState& worldState)
	{
		this->onCreate__(worldState);
	}

	void PhysicForm::onUpdate_(WorldState& worldState, float deltaTime)
	{
		this->tran.move(deltaTime * this->positionVel);

		this->onUpdate__(worldState, deltaTime);
	}
}
