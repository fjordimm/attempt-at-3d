
#include "AttemptAt3D/(Form)/PhysicForm.hpp"

namespace AttemptAt3D
{
	/* Constructors */
	
	PhysicForm::PhysicForm(WorldState& worldState) : Form(worldState),
		velocity(Vecs::Zero),
		friction(0.0f)
	{}

	/* Methods */

	void PhysicForm::onCreate_(WorldState& worldState)
	{
		this->onCreate__(worldState);
	}

	void PhysicForm::onUpdate_(WorldState& worldState, float deltaTime)
	{
		this->tran.move(deltaTime * this->velocity);
		this->velocity *= 1.0f - this->friction * deltaTime;

		this->onUpdate__(worldState, deltaTime);
	}
}
