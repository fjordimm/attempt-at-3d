
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
		_position(Vecs::Zero),
		_mayHaveChangedRotation(true),
		_rotation(Quats::Identity),
		_mayHaveChangedScale(true),
		_scale(Vecs::One)
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

	const Vec& Tran::get_forwardVec()
	{
		if (this->_mayHaveChangedRotation)
		{
			this->_updateRotationDeps();
			this->_mayHaveChangedRotation = false;
		}

		return this->_cached_forwardVec;
	}

	const Vec& Tran::get_upVec()
	{
		if (this->_mayHaveChangedRotation)
		{
			this->_updateRotationDeps();
			this->_mayHaveChangedRotation = false;
		}

		return this->_cached_upVec;
	}

	const Vec& Tran::get_rightVec()
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
		ret << "{pos" << Vecs::ToString(this->_position).c_str() << " rot" << Vecs::ToString(this->getEulerAngles()).c_str() << " scale" << Vecs::ToString(this->_scale).c_str() << "}";
		return ret.str();
	}
	
	Vec Tran::getEulerAngles() const
	{
		return glm::eulerAngles(this->_rotation);
	}

	void Tran::move(const Vec& translation)
	{
		this->acq_position() += translation;
	}
	
	void Tran::locallyMove(const Vec& translation)
	{
		this->acq_position() += this->get_rotation() * translation;
	}

	void Tran::moveAlong(const Vec& axis, float distance)
	{
		this->acq_position() += distance * axis;
	}

	void Tran::locallyMoveAlong(const Vec& axis, float distance)
	{
		this->acq_position() += distance * (this->get_rotation() * axis);
	}

	void Tran::rotate(const Vec& axis, float radians)
	{
		this->acq_rotation() = glm::angleAxis(radians, axis) * this->get_rotation();
	}

	void Tran::locallyRotate(const Vec& axis, float radians)
	{
		this->acq_rotation() = this->get_rotation() * glm::angleAxis(radians, axis);
	}

	void Tran::lookTowards(const Vec& target, const Vec& up)
	{
		Vec newForwards = glm::normalize(target - this->get_position());

		Vec xAxis = glm::normalize(glm::cross(newForwards, up));
		Vec yAxis = newForwards;
		Vec zAxis = glm::normalize(glm::cross(xAxis, newForwards));
		glm::mat3 rotationMatrix = glm::mat3(xAxis, yAxis, zAxis);

		this->acq_rotation() = glm::quat_cast(rotationMatrix);
	}

	void Tran::_updatePositionDeps()
	{
		this->_cached_positionMatrix = glm::translate(IdentityMat, this->_position);
	}

	void Tran::_updateRotationDeps()
	{
		this->_cached_rotationMatrix = glm::mat4_cast(this->_rotation);
		this->_cached_forwardVec = glm::rotate(this->_rotation, Vecs::Forwards);
		this->_cached_upVec = glm::rotate(this->_rotation, Vecs::Up);
		this->_cached_rightVec = glm::rotate(this->_rotation, Vecs::Right);
	}
	
	void Tran::_updateScaleDeps()
	{
		this->_cached_scaleMatrix = glm::scale(IdentityMat, this->_scale);
	}
}
