
#pragma once

#include "AttemptAt3D/(Util)/(Tran)/Vec.hpp"

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

	   public:
		Vec toVec() const;
	};

	namespace Colors
	{
		static const Color Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
		static const Color DarkGray = Color(0.25f, 0.25f, 0.25f, 1.0f);
		static const Color Gray = Color(0.5f, 0.5f, 0.5f, 1.0f);
		static const Color LightGray = Color(0.75f, 0.75f, 0.75f, 1.0f);
		static const Color White = Color(1.0f, 1.0f, 1.0f, 1.0f);
		static const Color Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
		static const Color Orange = Color(1.0f, 0.3f, 0.0f, 1.0f);
		static const Color Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
		static const Color Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
		static const Color Cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);
		static const Color Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
		static const Color Purple = Color(0.3f, 0.0f, 1.0f, 1.0f);
		static const Color Magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
	}
}
