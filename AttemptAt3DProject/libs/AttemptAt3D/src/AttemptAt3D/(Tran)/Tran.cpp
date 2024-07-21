
#include "AttemptAt3D/(Tran)/Tran.hpp"

#include <sstream>

namespace AttemptAt3D
{
	/* Constructors */

	Trans::Trans() :
		_hasChangedPosition(true),
		position(Vec3s::Zero),
		_hasChangedRotation(true),
		rotationQuat()
	{}

	Trans::Trans(const Trans& that) :
		scale(other.scale),
		rot(other.rot),
		pos(other.pos)
	{}

	Trans& Trans::operator=(const Trans& that)
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

	std::string Trans::toString() const
	{
		std::ostringstream ret;
		ret << "{pos" << Vec3s::ToString(this->position) << " rot" << "(---)" << " scale" << Vec3s::ToString(this->scale) << "}";
		return ret.str();
	}
}
