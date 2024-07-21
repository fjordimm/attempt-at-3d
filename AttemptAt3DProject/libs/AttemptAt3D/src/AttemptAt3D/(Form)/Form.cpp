
#include "AttemptAt3D/(Form)/Form.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Form::Form(ShaderManager& shaderManager, BodyManager& bodyManager, const Tran& tran, std::unique_ptr<Mesh> mesh) :
		tran(tran),
		mesh(std::move(mesh))
	{
		bodyReference = bodyManager.addNewBody(shaderManager, &this->tran, this->mesh.get());
	}
}
