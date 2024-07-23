
#pragma once

#include <cmath>
#include "AttemptAt3D/(Math)/_constants.hpp"

namespace AttemptAt3D::Math
{
	inline float RoughlyEqual(float a, float b, float epsilon = Math::Epsilon)
	{ return std::abs(a - b) < epsilon; }
}
