
#include "AttemptAt3D/(Form)/Form.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Form::Form(WorldState& worldState, std::unique_ptr<Mesh> mesh) :
		tran(),
		mesh(std::move(mesh)),
		drawObj(worldState.shaderManager, &this->tran, this->mesh.get())
	{}

	/* Methods */

	void Form::draw(ShaderManager& shaderManager) const
	{
		this->drawObj.draw(shaderManager);
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
