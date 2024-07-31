
#include "AttemptAt3D/(Form)/Forms/Sun.hpp"

#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"

namespace AttemptAt3D::Forms
{
	/* Constructors */

	Sun::Sun(WorldState& worldState) : Form(worldState),
		brightness(1.0f),
		ambientLight(0.0f),
		color(Colors::White)
	{}

	/* Methods */

	void Sun::recalculateAndApplySunRotMatrix(WorldState& worldState)
	{
		worldState.shaderProgramManager.setSunRotMatrix(this->tran.getRotationMatrix());
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
