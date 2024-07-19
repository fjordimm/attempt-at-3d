
#include "AttemptAt3D/ShaderManager/ShaderManager.hpp"

#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
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
	{}

	/* Methods */

	void ShaderManager::compileAndActivateShaders()
	{
		Debug::Log("compileAndActivateShaders");

		std::unique_ptr<const std::string> _vertexShaderSource = FileLoading::LoadFile(VERTEX_SHADER_SOURCE_PATH);
		const char* vertexShaderSource = _vertexShaderSource->c_str();
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(this->vertexShader);
		checkShaderCompilation(this->vertexShader);

		std::unique_ptr<const std::string> _geometryShaderSource = FileLoading::LoadFile(GEOMETRY_SHADER_SOURCE_PATH);
		const char* geometryShaderSource = _geometryShaderSource->c_str();
		this->geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(this->geometryShader, 1, &geometryShaderSource, nullptr);
		glCompileShader(this->geometryShader);
		checkShaderCompilation(this->geometryShader);

		std::unique_ptr<const std::string> _fragmentShaderSource = FileLoading::LoadFile(FRAGMENT_SHADER_SOURCE_PATH);
		const char* fragmentShaderSource = _fragmentShaderSource->c_str();
		this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(this->fragmentShader);
		checkShaderCompilation(this->fragmentShader);

		this->shaderProgram = glCreateProgram();
		glAttachShader(this->shaderProgram, this->vertexShader);
		glAttachShader(this->shaderProgram, this->geometryShader);
		glAttachShader(this->shaderProgram, this->fragmentShader);

		glLinkProgram(this->shaderProgram);
		glUseProgram(this->shaderProgram);

		this->attrib_position = glGetAttribLocation(this->shaderProgram, "position");
		glEnableVertexAttribArray(this->attrib_position);
		glVertexAttribPointer(this->attrib_position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

		this->attrib_color = glGetAttribLocation(this->shaderProgram, "color");
		glEnableVertexAttribArray(this->attrib_color);
		glVertexAttribPointer(this->attrib_color, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		this->uni_model = glGetUniformLocation(this->shaderProgram, "model");
		// glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 uni_model_val = glm::mat4(1.0f);
		glUniformMatrix4fv(this->uni_model, 1, GL_FALSE, glm::value_ptr(uni_model_val));

		this->uni_view = glGetUniformLocation(this->shaderProgram, "view");
		glm::mat4 uni_view_val = glm::lookAt(
			glm::vec3(0.0f, -5.0f, 5.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		glUniformMatrix4fv(this->uni_view, 1, GL_FALSE, glm::value_ptr(uni_view_val));

		this->uni_proj = glGetUniformLocation(this->shaderProgram, "proj");
		glm::mat4 uni_proj_val = glm::perspective(glm::radians(45.0f), 1.0f /*aspect ratio*/, 1.0f, 10.0f);
		glUniformMatrix4fv(this->uni_proj, 1, GL_FALSE, glm::value_ptr(uni_proj_val));

		// this->uni_sunRot = glGetUniformLocation(this->shaderProgram, "sunRot");
		// glm::mat4 uni_sunRot_val;
		// {
		// 	glm::quat quatX = glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		// 	glm::mat4 rotX = glm::toMat4(quatX);
		// 	glm::quat quatY = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		// 	glm::mat4 rotY = glm::toMat4(quatY);
		// 	uni_sunRot_val = rotY * rotX;
		// }
		// glUniformMatrix4fv(this->uni_sunRot, 1, GL_FALSE, glm::value_ptr(uni_sunRot_val));
		this->uni_sunRot = glGetUniformLocation(shaderProgram, "sunRot");
		glm::quat sunQuatX = glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 sunRotX = glm::toMat4(sunQuatX);
		glm::quat sunQuatY = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 sunRotY = glm::toMat4(sunQuatY);
		glUniformMatrix4fv(this->uni_sunRot, 1, GL_FALSE, glm::value_ptr(sunRotY * sunRotX));
	}

	void ShaderManager::cleanupForGl()
	{
		glDeleteProgram(this->shaderProgram);
		glDeleteShader(this->vertexShader);
		glDeleteShader(this->fragmentShader);
		glDeleteShader(this->geometryShader);
	}

	void ShaderManager::checkShaderCompilation(GLuint shader)
	{
		Debug::Log("Checking!!!!!!!!!!");

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
