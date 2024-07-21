
#include "AttemptAt3D/(Tran)/Tran.hpp"

#include <sstream>

namespace AttemptAt3D
{
	/* Constants */

	static const glm::mat4 IdentityMat = glm::mat4(1.0f);

	/* Constructors */

	Tran::Tran() :
		_position(Vec3s::Zero),
		_hasChangedPositionMatrix(true),
		_rotation(Quats::Identity),
		_hasChangedRotationMatrix(true),
		_hasChangedForwardVec(true),
		_scale(Vec3s::One),
		_hasChangedScaleMatrix(true)
	{}

	Tran::Tran(const Tran& that) :
		_position(that._position),
		_hasChangedPositionMatrix(that._hasChangedPositionMatrix),
		_positionMatrix(that._positionMatrix),
		_rotation(that._rotation),
		_hasChangedRotationMatrix(that._hasChangedRotationMatrix),
		_hasChangedForwardVec(that._hasChangedForwardVec),
		_scale(that._scale),
		_hasChangedScaleMatrix(that._hasChangedScaleMatrix),
		_scaleMatrix(that._scaleMatrix)
	{}

	Tran& Tran::operator=(const Tran& that)
	{
		_position = that._position;
		_hasChangedPositionMatrix = that._hasChangedPositionMatrix;
		_positionMatrix = that._positionMatrix;
		_rotation = that._rotation;
		_hasChangedRotationMatrix = that._hasChangedRotationMatrix;
		_hasChangedForwardVec = that._hasChangedForwardVec;
		_scale = that._scale;
		_hasChangedScaleMatrix = that._hasChangedScaleMatrix;
		_scaleMatrix = that._scaleMatrix;
		
        return *this;
	}

	/* Getters and Setters */

	const glm::mat4& Tran::get_positionMatrix()
	{
		if (this->_hasChangedPositionMatrix)
		{
			this->_positionMatrix = glm::translate(IdentityMat, this->_position);

			this->_hasChangedPositionMatrix = false;
		}

		return this->_positionMatrix;
	}

	const glm::mat4& Tran::get_rotationMatrix()
	{
		if (this->_hasChangedRotationMatrix)
		{
			this->_rotationMatrix = glm::mat4_cast(this->_rotation);

			this->_hasChangedRotationMatrix = false;
		}

		return this->_rotationMatrix;
	}

	const Vec3& Tran::get_forwardVec()
	{
		if (this->_hasChangedForwardVec)
		{
			this->_forwardVec = glm::rotate(this->_rotation, Vec3s::Forwards);

			this->_hasChangedForwardVec = false;
		}

		return this->_forwardVec;
	}
	
	const glm::mat4 Tran::get_scaleMatrix()
	{
		if (this->_hasChangedScaleMatrix)
		{
			this->_scaleMatrix = glm::scale(IdentityMat, this->_scale);

			this->_hasChangedScaleMatrix = false;
		}

		return this->_scaleMatrix;
	}
	
	
	/* Methods */

	std::string Tran::toString() const
	{
		std::ostringstream ret;
		ret << "{pos" << Vec3s::ToString(this->_position) << " rot" << Vec3s::ToString(this->getEulerAngles()) << " scale" << Vec3s::ToString(this->_scale) << "}";
		return ret.str();
	}
	
	const Vec3& Tran::getEulerAngles() const
	{
		return glm::eulerAngles(this->_rotation);
	}
}
