
#include "AttemptAt3D/(Trans)/Trans.hpp"

#include <sstream>

namespace AttemptAt3D
{
	/* Constructors */

	Trans::Trans() :
		scale(1.0f, 1.0f, 1.0f),
		rot(0.0f, 0.0f, 0.0f),
		pos(0.0f, 0.0f, 0.0f)
	{}

	Trans::Trans(const Vec3Scale& scale, const Vec3Rot& rot, const Vec3Pos& pos) :
		scale(scale),
		rot(rot),
		pos(pos)
	{}

	Trans::Trans(const Trans& other) :
		scale(other.scale),
		rot(other.rot),
		pos(other.pos)
	{}

	Trans& Trans::operator=(const Trans& other)
	{
		if (this != &other)
		{
            this->scale = other.scale;
            this->rot = other.rot;
            this->pos = other.pos;
        }
		
        return *this;
	}

	/* Methods */

	std::string Trans::toString()
	{
		std::ostringstream ret;
		ret << "{pos" << this->pos.toString() << " rot" << this->rot.toString() << " scale" << this->scale.toString() << "}";
		return ret.str();
	}
}
