
#include "AttemptAt3D/(InputManager)/InputManager.hpp"

#include <vector>
#include "AttemptAt3D/(PtrForGlfw)/PtrForGlfw.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constants */

	static const std::vector<int> KEYS
	{
		GLFW_KEY_W,
		GLFW_KEY_S
	};

	/* Constructors */

	InputManager::InputManager() :
		keyMap()
	{
		for (const int& key : KEYS)
		{
			this->keyMap[key] = false;
		}
	}

	/* Methods */

	void InputManager::setKeyCallbackForGlfw(GLFWwindow* windowForGlfw)
	{
		glfwSetKeyCallback(windowForGlfw, InputManager::keyCallback);
	}

	/* Operator Overloads */

	bool InputManager::operator[](int key)
	{
		auto tryGet = this->keyMap.find(key);
		if (tryGet != this->keyMap.end())
		{
			return tryGet->second;
		}
		else
		{
			Debug::LogWarning("Checking for a key that is not registered.");
			return false;
		}
	}

	/* Methods for External Use */

	void InputManager::keyCallback(GLFWwindow* windowForGlfw, int key, int scancode, int action, int mods)
	{
		InputManager* self = PtrForGlfw::Retrieve(windowForGlfw)->get<InputManager>();

		auto tryGet = self->keyMap.find(key);
		if (tryGet != self->keyMap.end())
		{
			if (action == GLFW_PRESS)
			{
				tryGet->second = true;
			}
			else if (action == GLFW_RELEASE)
			{
				tryGet->second = false;
			}
		}
	}
}
