
#include "AttemptAt3D/(Form)/Form.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Form::Form(ShaderManager& shaderManager, std::unique_ptr<Mesh> mesh) :
		tran(),
		mesh(std::move(mesh)),
		drawObj(shaderManager, &this->tran, this->mesh.get())
	{}

	/* Methods */

	void Form::draw(ShaderManager& shaderManager) const
	{
		this->drawObj.draw(shaderManager);
	}
}
