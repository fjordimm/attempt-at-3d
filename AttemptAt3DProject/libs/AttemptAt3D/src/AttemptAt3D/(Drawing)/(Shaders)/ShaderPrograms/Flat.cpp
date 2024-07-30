
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/Flat.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	/* Constructors */

	Flat::Flat() {}

	/* Methods */

	const char* Flat::getVertexShaderSourcePath() const
	{
		return "res/shaders/Flat/vertex.glsl";
	}

	const char* Flat::getGeometryShaderSourcePath() const
	{
		return "res/shaders/Flat/geometry.glsl";
	}
	
	const char* Flat::getFragmentShaderSourcePath() const
	{
		return "res/shaders/Flat/fragment.glsl";
	}
}
