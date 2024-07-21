
#pragma once

#include <string>
#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"
#include "AttemptAt3D/(Tran)/Vec3.hpp"
#include "AttemptAt3D/(Tran)/Quat.hpp"

namespace AttemptAt3D
{
	class Trans
	{
		/* Fields */

	   private:
		bool _hasChangedPosition;
		Vec3 position;
		glm::mat4 _positionMatrix;

		bool _hasChangedRotation;
		Quat rotationQuat;
		glm::mat4 _rotationMatrix;
		Vec3 _forwardVec;

		bool _hasChangedScale;
		Vec3 scale;
		glm::mat4 _scaleMatrix;

		/* Getters and Setters */

	   public:
		inline const Vec3& get_position() const { return this->position; }
		inline const Quat& get_rotationQuat() const { return this->rotationQuat; }
		inline const Vec3& get_scale() const { return this->scale; }
		inline Vec3& acq_position() { this->_hasChangedPosition = true; return this->position; }
		inline Quat& acq_rotationQuat() { this->_hasChangedRotation = true; return this->rotationQuat; }
		inline Vec3& acq_scale() { this->_hasChangedScale = true; return this->scale; }
		
		const glm::mat4& get_positionMatrix();
		const glm::mat4& get_rotationMatrix();
		const Vec3& get_forwardVec();
		const glm::mat4 get_scaleMatrix();


		/* Constructors */

	   public:
		Trans();
		// Trans(const Vec3Scale& scale, const Vec3Rot& rot, const Vec3Pos& pos);
		Trans(const Trans& that);
		Trans& operator=(const Trans& that);

		/* Methods */

	   public:
		std::string toString() const;
		const Vec3& getEulerAngles() const;
	};
}
