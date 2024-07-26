
#include "AttemptAt3D/(Form)/Form.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Form::Form(WorldState& worldState, Mesh* mesh) :
		tran(),
		mesh(mesh)
	{}

	/* Methods */

	void Form::draw(ShaderManager& shaderManager)
	{
		this->mesh->draw(shaderManager, this->tran);
	}

	void Form::onCreate(WorldState& worldState)
	{
		this->onCreate_(worldState);
	}

	void Form::onUpdate(WorldState& worldState, float deltaTime)
	{
		this->onUpdate_(worldState, deltaTime);
	}
}
