
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "AttemptAt3D/BodyManager/BodyManager.h"

namespace AttemptAt3D
{
	class Head
	{
		/* Fields */

	   private:
		GLFWwindow* windowForGlfw;

		BodyManager bodyManager;

		/* Getters and Setters */

	   public:
		inline BodyManager& get_bodyManager() { return this->bodyManager; }

		/* Constructors */

	   public:
		Head(const Head&) = delete;
		Head& operator=(const Head&) = delete;
		Head(Head&&) {}

		Head();

		/* Methods */

	   public:
		void start(int windowWidth = 600, int windowHeight = 600, const std::string windowTitle = "Placeholder Window Title");
	
	   private:
		void mainLoop();
	};
}
