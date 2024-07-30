
#pragma once

#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/ThreeDShape.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	class Flat : public ShaderPrograms::ThreeDShape
	{
		/* Constructors */

	   public:
		Flat(const Flat&) = delete;
		Flat& operator=(const Flat&) = delete;
		
		Flat();

		/* Methods */

		const char* getVertexShaderSourcePath() const final;
		const char* getGeometryShaderSourcePath() const final;
		const char* getFragmentShaderSourcePath() const final;
	};
}
