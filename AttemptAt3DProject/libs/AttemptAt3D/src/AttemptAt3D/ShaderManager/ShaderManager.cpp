
#include <cstdio>
#include "AttemptAt3D/ShaderManager/ShaderManager.hpp"
#include "AttemptAt3D/FileLoading/FileLoading.hpp"
#include "AttemptAt3D/Debug/Debug.hpp"

namespace AttemptAt3D
{
	/* Constants */

	static constexpr char VERTEX_SHADER_SOURCE_PATH[] = "res/shaders/vertexShaderSource.glsl";
	static constexpr char GEOMETRY_SHADER_SOURCE_PATH[] = "res/shaders/geometryShaderSource.glsl";
	static constexpr char FRAGMENT_SHADER_SOURCE_PATH[] = "res/shaders/fragmentShaderSource.glsl";

	/* Constructors */

	ShaderManager::ShaderManager() :
		vertexShaderSource(nullptr),
		geometryShaderSource(nullptr),
		fragmentShaderSource(nullptr),
		vertexShader(-1),
		geometryShader(-1),
		fragmentShader(-1),
		shaderProgram(-1),
		attrib_position(-1),
		attrib_color(-1),
		uni_model(-1),
		uni_view(-1),
		uni_proj(-1),
		uni_sunRot(-1)
	{
		this->vertexShaderSource = FileLoading::LoadFile(VERTEX_SHADER_SOURCE_PATH);
		this->geometryShaderSource = FileLoading::LoadFile(GEOMETRY_SHADER_SOURCE_PATH);
		this->fragmentShaderSource = FileLoading::LoadFile(FRAGMENT_SHADER_SOURCE_PATH);
	}

	ShaderManager::~ShaderManager()
	{
		delete[] this->vertexShaderSource;
		delete[] this->geometryShaderSource;
		delete[] this->fragmentShaderSource;
	}

	/* Methods */

	void ShaderManager::compileAndActivateShaders()
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);
		checkShaderCompilation(vertexShader);
	}

	void ShaderManager::checkShaderCompilation(GLuint shader)
	{
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (status)
		{ return; }
		else
		{
			static char buf[512];
			glGetShaderInfoLog(shader, 512, nullptr, buf);
			Debug::LogWarning("Shader did not compile. Output...");
			Debug::Printf("%s\n", buf);
			Debug::Exit();
		}
	}
}
