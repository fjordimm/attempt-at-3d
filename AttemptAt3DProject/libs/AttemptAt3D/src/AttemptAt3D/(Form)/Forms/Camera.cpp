
#include "AttemptAt3D/(Form)/Forms/Camera.hpp"

#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"

namespace AttemptAt3D::Forms
{
	/* Methods */

	void Camera::recalculateAndApplyViewMatrix(ShaderManager& shaderManager)
	{
		glm::mat4 viewMatrix = glm::lookAt(
			this->tran.getPosition(),
			this->tran.getPosition() + this->tran.getForwardVec(),
			this->tran.getUpVec()
		);

		shaderManager.setUni_viewVal(viewMatrix);
	}
}
