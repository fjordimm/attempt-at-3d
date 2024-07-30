
#include "AttemptAt3D/(Util)/(Tran)/Vec.hpp"

#include <sstream>
#include <cmath>

namespace AttemptAt3D::Vecs
{
	std::string ToString(const Vec& subj)
	{
		std::ostringstream ret;
		ret << "(" << subj.x << ", " << subj.y << ", " << subj.z << ")";
		return ret.str();
	}

	bool RoughlyEqual(const Vec& a, const Vec& b, float epsilon)
	{
		return
			(std::abs(a.x - b.x) < epsilon)
			&& (std::abs(a.y - b.y) < epsilon)
			&& (std::abs(a.z - b.z) < epsilon);
	}
}
