
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

	static const std::vector<int> MOUSE_BUTTONS
	{
		GLFW_MOUSE_BUTTON_LEFT,
		GLFW_MOUSE_BUTTON_RIGHT,
		GLFW_MOUSE_BUTTON_MIDDLE
	};

	static const InputVal FALSE_FALSE_INPUT = InputVal(false, false);

	/* Constructors */

	InputManager::InputManager() :
		keyDict(),
		anyKey(FALSE_FALSE_INPUT),
		_keyCount(0),
		mouseButtonDict(),
		anyMouseButton(FALSE_FALSE_INPUT),
		_mouseButtonCount(0),
		cursorX(0.0f),
		cursorY(0.0f),
		deltaCursorX(0.0f),
		deltaCursorY(0.0f)
	{
		for (const int& key : KEYS)
		{
			this->keyDict[key] = FALSE_FALSE_INPUT;
		}

		for (const int& mb : MOUSE_BUTTONS)
		{
			this->mouseButtonDict[mb] = FALSE_FALSE_INPUT;
		}
	}

	/* Methods */

	void InputManager::giveWindowForGlfw(GLFWwindow* windowForGlfw)
	{
		glfwSetKeyCallback(windowForGlfw, InputManager::keyCallback);
		glfwSetMouseButtonCallback(windowForGlfw, InputManager::mouseButtonCallback);
		glfwSetCursorPosCallback(windowForGlfw, InputManager::cursorPosCallback);
	}

	void InputManager::nextLoopIteration()
	{
		for (const int& key : KEYS)
		{
			this->keyDict[key].pressedOnce = false;
		}

		this->anyKey.pressedOnce = false;

		for (const int& mb : MOUSE_BUTTONS)
		{
			this->mouseButtonDict[mb].pressedOnce = false;
		}

		this->anyMouseButton.pressedOnce = false;

		this->deltaCursorX = 0.0f;
		this->deltaCursorY = 0.0f;
	}

	const InputVal& InputManager::getKey(int key) const
	{
		auto tryGet = this->keyDict.find(key);
		if (tryGet != this->keyDict.end())
		{
			return tryGet->second;
		}
		else
		{
			Debug::LogWarning("Checking for a key that is not registered.");
			return FALSE_FALSE_INPUT;
		}
	}

	const InputVal& InputManager::getMouseButton(int mouseButton) const
	{
		auto tryGet = this->mouseButtonDict.find(mouseButton);
		if (tryGet != this->mouseButtonDict.end())
		{
			return tryGet->second;
		}
		else
		{
			Debug::LogWarning("Checking for a mouse button that is not registered.");
			return FALSE_FALSE_INPUT;
		}
	}

	/* Methods for External Use */

	void InputManager::keyCallback(GLFWwindow* windowForGlfw, int key, int scancode, int action, int mods)
	{
		InputManager* self = PtrForGlfw::Retrieve(windowForGlfw)->get<InputManager>();

		auto tryGet = self->keyDict.find(key);
		if (tryGet != self->keyDict.end())
		{
			if (action == GLFW_PRESS)
			{
				if (!tryGet->second.isDown)
				{
					tryGet->second.pressedOnce = true;
					self->anyKey.pressedOnce = true;

					tryGet->second.isDown = true;
					self->_keyCount++;
				}
			}
			else if (action == GLFW_RELEASE)
			{
				if (tryGet->second.isDown)
				{
					tryGet->second.isDown = false;
					self->_keyCount--;
				}
			}

			if (self->_keyCount > 0)
			{ self->anyKey.isDown = true; }
			else
			{ self->anyKey.isDown = false; }
		}
	}

	void InputManager::mouseButtonCallback(GLFWwindow* windowForGlfw, int button, int action, int mods)
	{
		InputManager* self = PtrForGlfw::Retrieve(windowForGlfw)->get<InputManager>();

		auto tryGet = self->mouseButtonDict.find(button);
		if (tryGet != self->mouseButtonDict.end())
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
