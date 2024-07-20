
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

	   private:
		glm::mat4 mat;

		float x;
		float y;
		float z;

		/* Getters and Setters */

	   public:
		inline float get_x() { return this->x; }
		inline float get_y() { return this->y; }
		inline float get_z() { return this->z; }
		inline void set_x(float val);
		inline void set_y(float val);
		inline void set_z(float val);

		/* Constructors */

	   public:
		Vec3() = delete;

		Vec3(float x, float y, float z);
		Vec3(const Vec3&);
		Vec3& operator=(const Vec3&);

		/* Methods */

	   public:
		std::string toString();

	   protected:
		virtual void updateMat() = 0;

		/* Constants */

		// static constexpr Vec3 Zero = Vec3(0.0f, 0.0f, 0.0f);
	};

	class Vec3Pos : Vec3
	{

	};
}
