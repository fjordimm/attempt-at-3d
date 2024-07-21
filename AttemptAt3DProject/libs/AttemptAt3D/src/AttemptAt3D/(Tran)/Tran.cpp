
#include "AttemptAt3D/(Tran)/Tran.hpp"

#include <sstream>

namespace AttemptAt3D
{
	const glm::mat4& get_positionMatrix();
	const glm::mat4& get_rotationMatrix();
	const Vec3& get_forwardVec();
	const glm::mat4 get_scaleMatrix();
	
	/* Constructors */

	Trans::Trans() :
		_hasChangedPosition(true),
		position(Vec3s::Zero),
		_hasChangedRotation(true),
		rotationQuat(),
		_hasChangedScale(true),
		scale(Vec3s::One)
	{}

	Trans::Trans(const Trans& that) :
		_hasChangedPosition(that._hasChangedPosition),
		position(that.position),
		_positionMatrix(that._positionMatrix),
		_hasChangedRotation(that._hasChangedRotation),
		rotationQuat(that.rotationQuat),
		_rotationMatrix(that._rotationMatrix),
		_forwardVec(that._forwardVec),
		_hasChangedScale(that._hasChangedScale),
		scale(that.scale),
		_scaleMatrix(that._scaleMatrix)
	{}

	Trans& Trans::operator=(const Trans& that)
	{
		_hasChangedPosition = that._hasChangedPosition;
		position = that.position;
		_positionMatrix = that._positionMatrix;
		_hasChangedRotation = that._hasChangedRotation;
		rotationQuat = that.rotationQuat;
		_rotationMatrix = that._rotationMatrix;
		_forwardVec = that._forwardVec;
		_hasChangedScale = that._hasChangedScale;
		scale = that.scale;
		_scaleMatrix = that._scaleMatrix;
		
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
