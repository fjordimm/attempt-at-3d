
#pragma once

#include "AttemptAt3D/(Form)/Form.hpp"

namespace AttemptAt3D
{
	class PhysicForm : public Form
	{
		/* Constructors */

	   public:
		PhysicForm() = delete;
		PhysicForm(const PhysicForm&) = delete;
		PhysicForm& operator=(const PhysicForm&) = delete;
		
		PhysicForm(ShaderManager& shaderManager, std::unique_ptr<Mesh> mesh);
		
		/* Fields */

	   private:
		Vec positionVel;
		Vec rotationVelAxis;
		float rotationVelRadians;

		/* Getters and Setters */

		inline const Vec& getPositionVel();
		inline const Vec& getRotationVelAxis();
		inline const Vec& getRotationVelRadians();

		/* Methods */
	};
}
