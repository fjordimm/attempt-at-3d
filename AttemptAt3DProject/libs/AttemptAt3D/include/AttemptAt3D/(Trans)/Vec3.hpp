
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

namespace AttemptAt3D
{
	class Vec3
	{
		/* Fields */

	   protected:
		glm::mat4 _mat;

		float _x;
		float _y;
		float _z;

		/* Getters and Setters */

	   public:
		inline const glm::mat4& matrix() const { return this->_mat; }
		inline float get_x() { return this->_x; }
		inline float get_y() { return this->_y; }
		inline float get_z() { return this->_z; }
		inline void set_x(float val);
		inline void set_y(float val);
		inline void set_z(float val);

		/* Constructors */

	   public:
		Vec3() = delete;

		Vec3(float x, float y, float z);
		Vec3(const Vec3& other);
		Vec3& operator=(const Vec3& other);

		/* Methods */

	   public:
		std::string toString();

	   protected:
		virtual void _updateMat();
	};

	class Vec3Scale : public Vec3
	{
		using Vec3::Vec3; // constructor inheritance
		void _updateMat();
	};

	class Vec3Rot : public Vec3
	{
		using Vec3::Vec3; // constructor inheritance
		void _updateMat();
	};

	class Vec3Pos : public Vec3
	{
		using Vec3::Vec3; // constructor inheritance
		void _updateMat();
	};
}
