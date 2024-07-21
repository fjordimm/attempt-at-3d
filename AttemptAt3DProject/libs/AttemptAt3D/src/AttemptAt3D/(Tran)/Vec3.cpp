
#include "AttemptAt3D/(Tran)/Vec3.hpp"

#include <sstream>

namespace AttemptAt3D::Vec3s
{
	std::string ToString(const Vec3& subj)
	{
		std::ostringstream ret;
		ret << "(" << subj.x << ", " << subj.y << ", " << subj.z << ")";
		return ret.str();
	}
}
