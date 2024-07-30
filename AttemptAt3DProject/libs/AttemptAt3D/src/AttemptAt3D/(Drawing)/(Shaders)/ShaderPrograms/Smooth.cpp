
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/Smooth.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	/* Constructors */

	Smooth::Smooth() {}

	/* Methods */

	const char* Smooth::getVertexShaderSourcePath() const
	{
		return "res/shaders/Smooth/vertex.glsl";
	}

	const char* Smooth::getGeometryShaderSourcePath() const
	{
		return "res/shaders/Smooth/geometry.glsl";
	}
	
	const char* Smooth::getFragmentShaderSourcePath() const
	{
		return "res/shaders/Smooth/fragment.glsl";
	}
}
