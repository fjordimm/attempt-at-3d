
#pragma once

namespace AttemptAt3D
{
	class Color
	{
		/* Constructors */

	   public:
		Color() = delete;

		Color(float r, float g, float b, float a);
		Color(const Color& that);
		Color& operator=(const Color& that);
		
		/* Fields */

	   public:
		float r;
		float g;
		float b;
		float a;

		/* Methods */
	};
}
