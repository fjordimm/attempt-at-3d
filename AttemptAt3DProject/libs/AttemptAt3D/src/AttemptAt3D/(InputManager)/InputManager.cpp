
#include "AttemptAt3D/(InputManager)/InputManager.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	InputManager::InputManager() :
		keyMap()
	{}

	/* Methods */

	void InputManager::setKeyCallbackForGlfw(GLFWwindow* windowForGlfw)
	{
		glfwSetKeyCallback(windowForGlfw, InputManager::keyCallback);
	}

	/* Methods for External Use */

	void InputManager::keyCallback(GLFWwindow* windowForGlfw, int key, int scancode, int action, int mods)
	{

	}
}
