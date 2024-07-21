
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
		inline float get_x() const { return this->_x; }
		inline float get_y() const { return this->_y; }
		inline float get_z() const { return this->_z; }
		void set_x(float val);
		void set_y(float val);
		void set_z(float val);

		/* Constructors */

	   public:
		Vec3() = delete;

		Vec3(float x, float y, float z);
		Vec3(const Vec3& other);
		Vec3& operator=(const Vec3& other);

		/* Methods */

	   public:
		std::string toString() const;

	   protected:
		virtual void _updateMat() = 0;
	};

	class Vec3Scale : public Vec3
	{
		/* Constructors */

	   public:
		Vec3Scale(float x, float y, float z);
		Vec3Scale(const Vec3& other);

		/* Methods */

	   public:
		void _updateMat() override;
	};

	class Vec3Rot : public Vec3
	{
		/* Constructors */
	
	   public:
		Vec3Rot(float x, float y, float z);
		Vec3Rot(const Vec3& other);

		/* Methods */

	   public:
		void _updateMat() override;
	};

	class Vec3Pos : public Vec3
	{
		/* Constructors */

	   public:
		Vec3Pos(float x, float y, float z);
		Vec3Pos(const Vec3& other);

		/* Methods */

	   public:
		void _updateMat() override;
	};
}
