
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
		Tran(const Tran& that);
		Tran& operator=(const Tran& that);

		/* Fields */

	   private:
		bool _mayHaveChangedPosition;
		Vec3 _position;
		glm::mat4 _cached_positionMatrix;

		bool _mayHaveChangedRotation;
		Quat _rotation;
		glm::mat4 _cached_rotationMatrix;
		Vec3 _cached_forwardVec;
		Vec3 _cached_upVec;
		Vec3 _cached_rightVec;

		bool _mayHaveChangedScale;
		Vec3 _scale;
		glm::mat4 _cached_scaleMatrix;

		/* Getters and Setters */

	   public:
		inline const Vec3& get_position() const { return this->_position; }
		inline const Quat& get_rotationQuat() const { return this->_rotation; }
		inline const Vec3& get_scale() const { return this->_scale; }
		inline Vec3& acq_position() { this->_mayHaveChangedPosition = true; return this->_position; }
		inline Quat& acq_rotation() { this->_mayHaveChangedRotation = true; return this->_rotation; }
		inline Vec3& acq_scale() { this->_mayHaveChangedScale = true; return this->_scale; }
		
		const glm::mat4& get_positionMatrix();
		const glm::mat4& get_rotationMatrix();
		const Vec3& get_forwardVec();
		const Vec3& get_upVec();
		const Vec3& get_rightVec();
		const glm::mat4 get_scaleMatrix();


		/* Methods */

	   public:
		std::string toString() const;
		Vec3 getEulerAngles() const;

	   private:
		void _updatePositionDeps();
		void _updateRotationDeps();
		void _updateScaleDeps();
	};
}
