
#pragma once

#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/HasNormals.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	class Smooth : public ShaderPrograms::HasNormals
	{
		/* Constructors */

	   public:
		Smooth(const Smooth&) = delete;
		Smooth& operator=(const Smooth&) = delete;
		
		Smooth();

		/* Methods */

		const char* getVertexShaderSourcePath() const final;
		const char* getGeometryShaderSourcePath() const final;
		const char* getFragmentShaderSourcePath() const final;
	};
}
