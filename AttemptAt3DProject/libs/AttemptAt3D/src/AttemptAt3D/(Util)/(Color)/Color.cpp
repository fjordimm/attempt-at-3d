
#include "AttemptAt3D/(Util)/(Color)/Color.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Color::Color(float r, float g, float b, float a) :
		r(r),
		g(g),
		b(b),
		a(a)
	{}

	Color::Color(const Color& that) :
		r(that.r),
		g(that.g),
		b(that.b),
		a(that.a)
	{}

	Color& Color::operator=(const Color& that)
	{
		this->r = that.r;
		this->g = that.g;
		this->b = that.b;
		this->a = that.a;

		return *this;
	}

	/* Methods */
}
