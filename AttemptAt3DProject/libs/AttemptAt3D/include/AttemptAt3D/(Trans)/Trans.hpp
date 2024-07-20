
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

namespace AttemptAt3D
{
	class Trans
	{
		/* Fields */

	   private:
		// glm::mat4 scaleMat;
		// glm::mat4 rotMat;
		// glm::mat4 posMat;
		glm::mat4 mat;

		Vec3 scale;

		Vec3 rot;

		Vec3 pos;

		/* Constructors */

	   public:
		Trans();
		Trans(const Trans&);
		Trans& operator=(const Trans&);

		/* Methods */

	   public:
		std::string toString();
		std::string toStringScale();
		std::string toStringRot();
		std::string toStringPos();
	};
}
