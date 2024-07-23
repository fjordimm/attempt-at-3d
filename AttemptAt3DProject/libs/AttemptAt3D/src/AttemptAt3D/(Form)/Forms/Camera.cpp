
#include "AttemptAt3D/(Form)/Forms/Camera.hpp"

#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"

namespace AttemptAt3D::Forms
{
	/* Constructors */

	Camera::Camera(ShaderManager& shaderManager)
		: Form(shaderManager, nullptr)
	{}

	/* Methods */

	void Camera::recalculateAndApplyViewMatrix(ShaderManager& shaderManager)
	{
		glm::mat4 viewMatrix = glm::lookAt(
			this->tran.get_position(),
			this->tran.get_position() + this->tran.get_forwardVec(),
			this->tran.get_upVec()
		);

		shaderManager.set_uni_viewVal(viewMatrix);
	}
}