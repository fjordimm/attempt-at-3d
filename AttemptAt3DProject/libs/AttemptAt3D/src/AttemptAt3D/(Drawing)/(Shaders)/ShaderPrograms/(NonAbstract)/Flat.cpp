
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(NonAbstract)/Flat.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	/* Constructors */

	Flat::Flat() {}

	/* Methods */

	const char* Flat::getVertexShaderSourcePath() const
	{
		return "res/shaders/vertexShaderSource.glsl";
	}

	const char* Flat::getGeometryShaderSourcePath() const
	{
		return "res/shaders/geometryShaderSource.glsl";
	}
	
	const char* Flat::getFragmentShaderSourcePath() const
	{
		return "res/shaders/fragmentShaderSource.glsl";
	}
}
