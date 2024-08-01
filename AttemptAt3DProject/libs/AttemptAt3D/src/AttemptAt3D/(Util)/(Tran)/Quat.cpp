
#include "AttemptAt3D/(Util)/(Tran)/Quat.hpp"

namespace AttemptAt3D::Quats
{
	Quat Rotate(const Quat& quat, const Vec& axis, float radians)
	{
		return glm::angleAxis(radians, axis) * quat;
	}

	Quat LocallyRotate(const Quat& quat, const Vec& axis, float radians)
	{
		return quat * glm::angleAxis(radians, axis);
	}

	Quat LookTowards(const Vec& position, const Vec& target, const Vec& up)
	{
		Vec newForwards = glm::normalize(target - position);

		Vec xAxis = glm::normalize(glm::cross(newForwards, up));
		Vec yAxis = newForwards;
		Vec zAxis = glm::normalize(glm::cross(xAxis, newForwards));
		glm::mat3 rotationMatrix = glm::mat3(xAxis, yAxis, zAxis);

		return glm::quat_cast(rotationMatrix);
	}
}
