
#include "AttemptAt3D/(Tran)/Vec.hpp"

#include <sstream>

namespace AttemptAt3D::Vecs
{
	std::string ToString(const Vec& subj)
	{
		std::ostringstream ret;
		ret << "(" << subj.x << ", " << subj.y << ", " << subj.z << ")";
		return ret.str();
	}
}
