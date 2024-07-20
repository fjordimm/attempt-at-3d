
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include "AttemptAt3D/(Trans)/Vec3.hpp"

namespace AttemptAt3D
{
	class Trans
	{
		/* Fields */

	   public:
		Vec3Scale scale;
		Vec3Rot rot;
		Vec3Pos pos;

		/* Constructors */

	   public:
		Trans();
		Trans(const Vec3Scale& scale, const Vec3Rot& rot, const Vec3Pos& pos);
		Trans(const Trans& other);
		Trans& operator=(const Trans& other);

		/* Methods */

	   public:
		std::string toString() const;
	};
}
