
#pragma once

#include <string>
#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"
#include "AttemptAt3D/(Tran)/Vec3.hpp"
#include "AttemptAt3D/(Tran)/Quat.hpp"

namespace AttemptAt3D
{
	class Tran
	{
		/* Constructors */

	   public:
		Tran();
		// Tran(const Vec3Scale& scale, const Vec3Rot& rot, const Vec3Pos& pos);
		Tran(const Tran& that) = delete;
		Tran& operator=(const Tran& that) = delete;

		/* Fields */

	   private:
		Vec3 _position;
		bool _hasChangedPositionMatrix;
		glm::mat4 _positionMatrix;

		Quat _rotation;
		bool _hasChangedRotationMatrix;
		glm::mat4 _rotationMatrix;
		bool _hasChangedForwardVec;
		Vec3 _forwardVec;

		Vec3 _scale;
		bool _hasChangedScaleMatrix;
		glm::mat4 _scaleMatrix;

		/* Getters and Setters */

	   public:
		inline const Vec3& get_position() const { return this->_position; }
		inline const Quat& get_rotationQuat() const { return this->_rotation; }
		inline const Vec3& get_scale() const { return this->_scale; }
		inline Vec3& acq_position() { this->_hasChangedPositionMatrix = true; return this->_position; }
		inline Quat& acq_rotationQuat() { this->_hasChangedRotationMatrix = true; this->_hasChangedForwardVec = true; return this->_rotation; }
		inline Vec3& acq_scale() { this->_hasChangedScaleMatrix = true; return this->_scale; }
		
		const glm::mat4& get_positionMatrix();
		const glm::mat4& get_rotationMatrix();
		const Vec3& get_forwardVec();
		const glm::mat4 get_scaleMatrix();


		/* Methods */

	   public:
		std::string toString() const;
		Vec3 getEulerAngles() const;
	};
}
