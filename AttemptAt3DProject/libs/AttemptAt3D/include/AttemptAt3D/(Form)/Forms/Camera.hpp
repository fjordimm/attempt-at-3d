
#pragma once

#include "AttemptAt3D/(Form)/Form.hpp"

namespace AttemptAt3D::Forms
{
	class Camera : public Form
	{
		/* Constructors */

	   public:
		Camera(ShaderManager& shaderManager);

		/* Methods */

	   public:
		void recalculateAndApplyViewMatrix(ShaderManager& shaderManager);
	};
}
