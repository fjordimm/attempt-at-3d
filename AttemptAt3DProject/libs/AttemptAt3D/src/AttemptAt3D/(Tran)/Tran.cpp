
#include "AttemptAt3D/(Tran)/Tran.hpp"

#include <sstream>
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constants */

	static const glm::mat4 IdentityMat = glm::mat4(1.0f);

	/* Constructors */

	Tran::Tran() :
		_mayHaveChangedPosition(true),
		_position(Vec3s::Zero),
		_mayHaveChangedRotation(true),
		_rotation(Quats::Identity),
		_mayHaveChangedScale(true),
		_scale(Vec3s::One)
	{}

	Tran::Tran(const Tran& that) :
		_mayHaveChangedPosition(that._mayHaveChangedPosition),
		_position(that._position),
		_cached_positionMatrix(that._cached_positionMatrix),
		_mayHaveChangedRotation(that._mayHaveChangedRotation),
		_rotation(that._rotation),
		_cached_rotationMatrix(that._cached_rotationMatrix),
		_cached_forwardVec(that._cached_forwardVec),
		_cached_upVec(that._cached_upVec),
		_cached_rightVec(that._cached_rightVec),
		_mayHaveChangedScale(that._mayHaveChangedScale),
		_scale(that._scale),
		_cached_scaleMatrix(that._cached_scaleMatrix)
	{}

	Tran& Tran::operator=(const Tran& that)
	{
		_mayHaveChangedPosition = that._mayHaveChangedPosition;
		_position = that._position;
		_cached_positionMatrix = that._cached_positionMatrix;
		_mayHaveChangedRotation = that._mayHaveChangedRotation;
		_rotation = that._rotation;
		_cached_rotationMatrix = that._cached_rotationMatrix;
		_cached_forwardVec = that._cached_forwardVec;
		_cached_upVec = that._cached_upVec;
		_cached_rightVec = that._cached_rightVec;
		_mayHaveChangedScale = that._mayHaveChangedScale;
		_scale = that._scale;
		_cached_scaleMatrix = that._cached_scaleMatrix;
		
        return *this;
	}

	/* Getters and Setters */

	const glm::mat4& Tran::get_positionMatrix()
	{
		if (this->_mayHaveChangedPosition)
		{
			this->_updatePositionDeps();
			this->_mayHaveChangedPosition = false;
		}

		return this->_cached_positionMatrix;
	}

	const glm::mat4& Tran::get_rotationMatrix()
	{
		if (this->_mayHaveChangedRotation)
		{
			this->_updateRotationDeps();
			this->_mayHaveChangedRotation = false;
		}

		return this->_cached_rotationMatrix;
	}

	const Vec3& Tran::get_forwardVec()
	{
		if (this->_mayHaveChangedRotation)
		{
			this->_updateRotationDeps();
			this->_mayHaveChangedRotation = false;
		}

		return this->_cached_forwardVec;
	}

	const Vec3& Tran::get_upVec()
	{
		if (this->_mayHaveChangedRotation)
		{
			this->_updateRotationDeps();
			this->_mayHaveChangedRotation = false;
		}

		return this->_cached_upVec;
	}

	const Vec3& Tran::get_rightVec()
	{
		if (this->_mayHaveChangedRotation)
		{
			this->_updateRotationDeps();
			this->_mayHaveChangedRotation = false;
		}

		return this->_cached_rightVec;
	}
	
	const glm::mat4 Tran::get_scaleMatrix()
	{
		if (this->_mayHaveChangedScale)
		{
			this->_updateScaleDeps();
			this->_mayHaveChangedScale = false;
		}

		return this->_cached_scaleMatrix;
	}
	
	/* Methods */

	std::string Tran::toString() const
	{
		std::ostringstream ret;
		ret << "{pos" << Vec3s::ToString(this->_position).c_str() << " rot" << Vec3s::ToString(this->getEulerAngles()).c_str() << " scale" << Vec3s::ToString(this->_scale).c_str() << "}";
		return ret.str();
	}
	
	Vec3 Tran::getEulerAngles() const
	{
		return glm::eulerAngles(this->_rotation);
	}

	void Tran::move(const Vec3& vec)
	{
		this->acq_position() += vec;
	}

	void Tran::moveAlong(const Vec3& vec, float dist)
	{
		this->acq_position() += dist * vec;
	}

	void Tran::locallyMove(const Vec3& vec)
	{
		this->acq_position() += this->get_rotation() * vec;
	}

	void Tran::_updatePositionDeps()
	{
		this->_cached_positionMatrix = glm::translate(IdentityMat, this->_position);
	}

	void Tran::_updateRotationDeps()
	{
		this->_cached_rotationMatrix = glm::mat4_cast(this->_rotation);
		this->_cached_forwardVec = glm::rotate(this->_rotation, Vec3s::Forwards);
		this->_cached_upVec = glm::rotate(this->_rotation, Vec3s::Up);
		this->_cached_rightVec = glm::rotate(this->_rotation, Vec3s::Right);
	}
	
	void Tran::_updateScaleDeps()
	{
		this->_cached_scaleMatrix = glm::scale(IdentityMat, this->_scale);
	}
}
