
#include "AttemptAt3D/(Form)/Form.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Form::Form(ShaderManager& shaderManager, BodyManager& bodyManager, const Trans& trans, std::unique_ptr<Mesh> mesh) :
		trans(trans),
		mesh(std::move(mesh))
	{
		bodyReference = bodyManager.addNewBody(shaderManager, &trans, this->mesh.get());
	}

	/* Methods */
}
