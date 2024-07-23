
#pragma once

#include <map>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AttemptAt3D
{
	class InputManager
	{
		/* Constructors */

	   public:
		InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;
		
		InputManager();
		
		/* Fields */

	   private:
		std::map<int, bool> keyMap;

		/* Methods */

	   public:
		void setKeyCallbackForGlfw(GLFWwindow* windowForGlfw);

		/* Methods for External Use */

	   private:
		static void keyCallback(GLFWwindow* windowForGlfw, int key, int scancode, int action, int mods);
	};
}
