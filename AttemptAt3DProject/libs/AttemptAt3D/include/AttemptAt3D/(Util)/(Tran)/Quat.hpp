
#pragma once

#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"
#include "AttemptAt3D/(Util)/(Tran)/Vec.hpp"

namespace AttemptAt3D
{
	typedef glm::quat Quat;

	namespace Quats
	{
		static const Quat Identity = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

		Quat Rotate(const Quat& quat, const Vec& axis, float radians);
		Quat LocallyRotate(const Quat& quat, const Vec& axis, float radians);
		Quat LookTowards(const Vec& position, const Vec& target, const Vec& up = Vecs::Up);
	}
}
