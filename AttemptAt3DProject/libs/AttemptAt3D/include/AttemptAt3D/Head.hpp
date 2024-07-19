
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "AttemptAt3D/BodyManager/BodyManager.hpp"
#include "AttemptAt3D/ShaderManager/ShaderManager.hpp"

namespace AttemptAt3D
{
	class Head
	{
		/* Fields */

	   private:
		GLFWwindow* windowForGlfw;

		ShaderManager shaderManager;
		BodyManager bodyManager;

		/* Getters and Setters */

	   public:
		inline ShaderManager& get_shaderManager() { return this->shaderManager; }
		inline BodyManager& get_bodyManager() { return this->bodyManager; }

		/* Constructors */

	   public:
		Head(const Head&) = delete;
		Head& operator=(const Head&) = delete;

		Head();

		/* Methods */

	   public:
		void start(int windowWidth = 600, int windowHeight = 600, const std::string windowTitle = "Placeholder Window Title");
	
	   private:
		void mainLoop();
		void endGlfw();
	};
}
