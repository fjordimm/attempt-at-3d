
#include "AttemptAt3D/(InputManager)/InputManager.hpp"

#include <vector>
#include "AttemptAt3D/(PtrForGlfw)/PtrForGlfw.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	using InputVal = InputManager::InputVal;

	/* Constants */

	static const std::vector<int> KEYS
	{
		GLFW_KEY_W,
		GLFW_KEY_S,
		GLFW_KEY_A,
		GLFW_KEY_D,
		GLFW_KEY_SPACE,
		GLFW_KEY_LEFT_SHIFT,
		GLFW_KEY_UP,
		GLFW_KEY_DOWN,
		GLFW_KEY_RIGHT,
		GLFW_KEY_LEFT,
		GLFW_KEY_ESCAPE
	};

	static const InputVal FALSE_FALSE_INPUT = InputVal(false, false);

	/* Constructors */

	InputManager::InputManager() :
		keyMap(),
		cursorX(0.0f),
		cursorY(0.0f),
		deltaCursorX(0.0f),
		deltaCursorY(0.0f)
	{
		for (const int& key : KEYS)
		{
			this->keyMap[key] = FALSE_FALSE_INPUT;
		}
	}

	/* Methods */

	void InputManager::giveWindowForGlfw(GLFWwindow* windowForGlfw)
	{
		glfwSetKeyCallback(windowForGlfw, InputManager::keyCallback);
		glfwSetCursorPosCallback(windowForGlfw, InputManager::cursorPosCallback);
	}

	void InputManager::nextLoopIteration()
	{
		for (const int& key : KEYS)
		{
			this->keyMap[key].pressedOnce = false;
		}

		this->deltaCursorX = 0.0f;
		this->deltaCursorY = 0.0f;
	}

	/* Operator Overloads */

	const InputVal& InputManager::operator[](int key) const
	{
		auto tryGet = this->keyMap.find(key);
		if (tryGet != this->keyMap.end())
		{
			return tryGet->second;
		}
		else
		{
			Debug::LogWarning("Checking for a key that is not registered.");
			return FALSE_FALSE_INPUT;
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
				if (!tryGet->second.isDown)
				{ tryGet->second.pressedOnce = true; }

				tryGet->second.isDown = true;
			}
			else if (action == GLFW_RELEASE)
			{
				tryGet->second.isDown = false;
			}
		}
	}

	void InputManager::cursorPosCallback(GLFWwindow* windowForGlfw, double xPos, double yPos)
	{
		InputManager* self = PtrForGlfw::Retrieve(windowForGlfw)->get<InputManager>();

		self->deltaCursorX = xPos - self->cursorX;
		self->deltaCursorY = yPos - self->cursorY;

		self->cursorX = xPos;
		self->cursorY = yPos;
	}
}
