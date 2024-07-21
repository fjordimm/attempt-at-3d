
#include "AttemptAt3D/(Trans)/Vec3.hpp"

#include <sstream>
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	///// Vec3 /////

	/* Getters and Setters */

	void Vec3::set_x(float val)
	{
		this->_x = val;
		this->_updateMat();
	}

	void Vec3::set_y(float val)
	{
		this->_y = val;
		this->_updateMat();
	}

	void Vec3::set_z(float val)
	{
		this->_z = val;
		this->_updateMat();
	}

	/* Constructors */

	Vec3::Vec3(float x, float y, float z) :
		_x(x),
		_y(y),
		_z(z)
	{}

	Vec3::Vec3(const Vec3& other) :
		_mat(other._mat),
		_x(other._x),
		_y(other._y),
		_z(other._z)
	{}

	Vec3& Vec3::operator=(const Vec3& other)
	{
		this->_mat = other._mat;
		this->_x = other._x;
		this->_y = other._y;
		this->_z = other._z;
		this->_updateMat();
		
        return *this;
	}

	/* Methods */

	std::string Vec3::toString() const
	{
		std::ostringstream ret;
		ret << "(" << this->_x << ", " << this->_y << ", " << this->_z << ")";
		return ret.str();
	}

	///// Vec3Scale /////

	/* Constructors */

	Vec3Scale::Vec3Scale(float x, float y, float z) : Vec3(x, y, z)
	{ this->_updateMat(); }

	Vec3Scale::Vec3Scale(const Vec3& other) : Vec3(other)
	{ this->_updateMat(); }

	/* Methods */

	void Vec3Scale::_updateMat()
	{
		this->_mat = glm::scale(glm::mat4(1.0f), glm::vec3(this->_x, this->_y, this->_z));
	}

	///// Vec3Rot /////

	/* Constructors */

	Vec3Rot::Vec3Rot(float x, float y, float z) : Vec3(x, y, z)
	{ this->_updateMat(); }

	Vec3Rot::Vec3Rot(const Vec3& other) : Vec3(other)
	{ this->_updateMat(); }

	/* Methods */

	void Vec3Rot::_updateMat()
	{
		// Note: the order I rotate is Y, X, Z

		glm::mat4 rotY = glm::toMat4(glm::angleAxis(this->_y, glm::vec3(0.0f, 1.0f, 0.0f)));
		glm::mat4 rotX = glm::toMat4(glm::angleAxis(this->_x, glm::vec3(1.0f, 0.0f, 0.0f)));
		glm::mat4 rotZ = glm::toMat4(glm::angleAxis(this->_z, glm::vec3(0.0f, 0.0f, 1.0f)));

		this->_mat = rotZ * rotX * rotY;
	}

	///// Vec3Pos /////

	/* Constructors */

	Vec3Pos::Vec3Pos(float x, float y, float z) : Vec3(x, y, z)
	{ this->_updateMat(); }

	Vec3Pos::Vec3Pos(const Vec3& other) : Vec3(other)
	{ this->_updateMat(); }

	/* Methods */

	void Vec3Pos::_updateMat()
	{
		this->_mat = glm::translate(glm::mat4(1.0f), glm::vec3(this->_x, this->_y, this->_z));
	}
}
