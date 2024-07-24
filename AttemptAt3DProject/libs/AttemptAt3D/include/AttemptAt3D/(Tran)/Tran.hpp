
#pragma once

#include <string>
#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"
#include "AttemptAt3D/(Tran)/Vec.hpp"
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
		Vec _position;
		glm::mat4 _cached_positionMatrix;

		bool _mayHaveChangedRotation;
		Quat _rotation;
		glm::mat4 _cached_rotationMatrix;
		Vec _cached_forwardVec;
		Vec _cached_upVec;
		Vec _cached_rightVec;

		bool _mayHaveChangedScale;
		Vec _scale;
		glm::mat4 _cached_scaleMatrix;

		/* Getters and Setters */

	   public:
		inline const Vec& getPosition() const { return this->_position; }
		inline const Quat& getRotation() const { return this->_rotation; }
		inline const Vec& getScale() const { return this->_scale; }
		inline Vec& acqPosition() { this->_mayHaveChangedPosition = true; return this->_position; }
		inline Quat& acqRotation() { this->_mayHaveChangedRotation = true; return this->_rotation; }
		inline Vec& acqScale() { this->_mayHaveChangedScale = true; return this->_scale; }
		
		const glm::mat4& getPositionMatrix();
		const glm::mat4& getRotationMatrix();
		const Vec& getForwardVec();
		const Vec& getUpVec();
		const Vec& getRightVec();
		const glm::mat4 getScaleMatrix();

		/* Methods */

	   public:
		std::string toString() const;
		Vec eulerAngles() const;

		void move(const Vec& translation);
		void moveAlong(const Vec& axis, float distance);
		void rotate(const Vec& axis, float radians);
		void lookTowards(const Vec& target, const Vec& up = Vecs::Up);

		void locallyMove(const Vec& translation);
		void locallyMoveAlong(const Vec& axis, float distance);
		void locallyRotate(const Vec& axis, float radians);

	   private:
		void _updatePositionDeps();
		void _updateRotationDeps();
		void _updateScaleDeps();
	};
}
