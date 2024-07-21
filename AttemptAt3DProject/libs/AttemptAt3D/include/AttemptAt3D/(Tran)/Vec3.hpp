
#pragma once

#include <string>
#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"

namespace AttemptAt3D
{
	typedef glm::vec3 Vec3;

	namespace Vec3s
	{
		std::string ToString(const Vec3& subj);

		static const Vec3 Zero = glm::vec3(0.0f, 0.0f, 0.0f);
		static const Vec3 One = glm::vec3(1.0f, 1.0f, 1.0f);
		static const Vec3 Forwards = glm::vec3(0.0f, 1.0f, 0.0f);
	}
}
