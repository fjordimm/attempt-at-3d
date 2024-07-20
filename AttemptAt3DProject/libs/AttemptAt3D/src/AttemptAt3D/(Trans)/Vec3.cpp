
#include "AttemptAt3D/(Trans)/Vec3.hpp"

#include <sstream>

namespace AttemptAt3D
{
	///// Vec3 /////

	/* Getters and Setters */

	inline void Vec3::set_x(float val)
	{
		this->_x = val;
		this->_updateMat();
	}

	inline void Vec3::set_y(float val)
	{
		this->_y = val;
		this->_updateMat();
	}

	inline void Vec3::set_z(float val)
	{
		this->_z = val;
		this->_updateMat();
	}

	/* Constructors */

	Vec3::Vec3(float x, float y, float z) :
		_x(x),
		_y(y),
		_z(z)
	{
		this->_updateMat();
	}

	Vec3::Vec3(const Vec3& other) :
		_mat(other._mat),
		_x(other._x),
		_y(other._y),
		_z(other._z)
	{}

	Vec3& Vec3::operator=(const Vec3& other)
	{
		if (this != &other)
		{
            this->_mat = other._mat;
            this->_x = other._x;
            this->_y = other._y;
            this->_z = other._z;
        }
		
        return *this;
	}

	/* Methods */

	std::string Vec3::toString() const
	{
		std::ostringstream ret;
		ret << "(" << this->_x << ", " << this->_y << ", " << this->_z << ")";
		return ret.str();
	}

	void Vec3::_updateMat()
	{
		this->_mat = glm::mat4(1.0f);
	}

	///// Vec3Scale /////

	/* Methods */

	void Vec3Scale::_updateMat()
	{
		this->_mat = glm::scale(glm::mat4(0.0f), glm::vec3(this->_x, this->_y, this->_z));
	}

	///// Vec3Rot /////

	/* Methods */

	void Vec3Rot::_updateMat()
	{
		this->_mat = glm::rotate(glm::mat4(0.0f), this->_x, glm::vec3(1.0f, 0.0f, 0.0f));
		this->_mat = glm::rotate(this->_mat, this->_y, glm::vec3(0.0f, 1.0f, 0.0f));
		this->_mat = glm::rotate(this->_mat, this->_z, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	///// Vec3Pos /////

	/* Methods */

	void Vec3Pos::_updateMat()
	{
		this->_mat = glm::translate(glm::mat4(0.0f), glm::vec3(this->_x, this->_y, this->_z));
	}
}
