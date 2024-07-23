
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
		inline const Vec& get_position() const { return this->_position; }
		inline const Quat& get_rotation() const { return this->_rotation; }
		inline const Vec& get_scale() const { return this->_scale; }
		inline Vec& acq_position() { this->_mayHaveChangedPosition = true; return this->_position; }
		inline Quat& acq_rotation() { this->_mayHaveChangedRotation = true; return this->_rotation; }
		inline Vec& acq_scale() { this->_mayHaveChangedScale = true; return this->_scale; }
		
		const glm::mat4& get_positionMatrix();
		const glm::mat4& get_rotationMatrix();
		const Vec& get_forwardVec();
		const Vec& get_upVec();
		const Vec& get_rightVec();
		const glm::mat4 get_scaleMatrix();

		/* Methods */

	   public:
		std::string toString() const;
		Vec getEulerAngles() const;

		void move(const Vec& vec);
		void moveAlong(const Vec& vec, float dist);
		void locallyMove(const Vec& vec);
		void locallyMoveAlong(const Vec& vec, float dist);
		void lookTowards(const Vec& target, const Vec& up = Vecs::Up);

	   private:
		void _updatePositionDeps();
		void _updateRotationDeps();
		void _updateScaleDeps();
	};
}
