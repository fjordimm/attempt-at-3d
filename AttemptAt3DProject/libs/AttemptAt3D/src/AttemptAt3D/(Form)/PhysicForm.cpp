
#include "AttemptAt3D/(Form)/PhysicForm.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	PhysicForm::PhysicForm(ShaderManager& shaderManager, std::unique_ptr<Mesh> mesh)
		: Form(shaderManager, std::move(mesh))
	{}

	/* Methods */
}
