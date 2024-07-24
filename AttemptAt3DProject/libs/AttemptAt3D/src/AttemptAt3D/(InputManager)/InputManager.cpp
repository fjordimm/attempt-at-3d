
#include "AttemptAt3D/(InputManager)/InputManager.hpp"

#include <vector>
#include "AttemptAt3D/(PtrForGlfw)/PtrForGlfw.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	using InputVal = InputManager::InputVal;

	/* Constants */

	// static const std::vector<int> KEYS
	// {
	// 	GLFW_KEY_W,
	// 	GLFW_KEY_S,
	// 	GLFW_KEY_A,
	// 	GLFW_KEY_D,
	// 	GLFW_KEY_SPACE,
	// 	GLFW_KEY_LEFT_SHIFT,
	// 	GLFW_KEY_UP,
	// 	GLFW_KEY_DOWN,
	// 	GLFW_KEY_RIGHT,
	// 	GLFW_KEY_LEFT,
	// 	GLFW_KEY_ESCAPE
	// };

	// static const std::vector<int> MOUSE_BUTTONS
	// {
	// 	GLFW_MOUSE_BUTTON_LEFT,
	// 	GLFW_MOUSE_BUTTON_RIGHT,
	// 	GLFW_MOUSE_BUTTON_MIDDLE
	// };

	static const InputVal FALSE_FALSE_INPUT = InputVal(false, false);

	/* Constructors */

	InputManager::InputManager() :
		keyDict(),
		anyKey(FALSE_FALSE_INPUT),
		_anyKeyCount(0),
		mouseButtonDict(),
		anyMouseButton(FALSE_FALSE_INPUT),
		_anyMouseButtonCount(0),
		cursorX(0.0f),
		cursorY(0.0f),
		deltaCursorX(0.0f),
		deltaCursorY(0.0f)
	{}

	/* Methods */

	void InputManager::giveWindowForGlfw(GLFWwindow* windowForGlfw)
	{
		glfwSetKeyCallback(windowForGlfw, InputManager::keyCallback);
		glfwSetMouseButtonCallback(windowForGlfw, InputManager::mouseButtonCallback);
		glfwSetCursorPosCallback(windowForGlfw, InputManager::cursorPosCallback);
	}

	void InputManager::nextLoopIteration()
	{
		for (auto iter = this->keyDict.begin(); iter != this->keyDict.end(); iter++)
		{
			iter->second.pressedOnce = false;
		}

		this->anyKey.pressedOnce = false;

		for (auto iter = this->mouseButtonDict.begin(); iter != this->mouseButtonDict.end(); iter++)
		{
			iter->second.pressedOnce = false;
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
			return FALSE_FALSE_INPUT;
		}
	}

	/* Methods for External Use */

	void InputManager::keyCallback(GLFWwindow* windowForGlfw, int key, int scancode, int action, int mods)
	{
		InputManager* self = PtrForGlfw::Retrieve(windowForGlfw)->get<InputManager>();

		// only replaces the item if it doesn't exist
		auto iter = self->keyDict.emplace(key, FALSE_FALSE_INPUT).first;

		if (action == GLFW_PRESS)
		{
			if (!iter->second.isDown)
			{
				iter->second.pressedOnce = true;
				self->anyKey.pressedOnce = true;

				iter->second.isDown = true;
				self->_anyKeyCount++;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			if (iter->second.isDown)
			{
				iter->second.isDown = false;
				self->_anyKeyCount--;
			}
		}

		if (self->_anyKeyCount > 0)
		{ self->anyKey.isDown = true; }
		else if (self->_anyKeyCount == 0)
		{ self->anyKey.isDown = false; }
		else
		{ Debug::LogWarning("InputManager::_anyKeyCount is below 0."); }
	}

	void InputManager::mouseButtonCallback(GLFWwindow* windowForGlfw, int button, int action, int mods)
	{
		InputManager* self = PtrForGlfw::Retrieve(windowForGlfw)->get<InputManager>();

		// only replaces the item if it doesn't exist
		auto iter = self->mouseButtonDict.emplace(button, FALSE_FALSE_INPUT).first;

		if (action == GLFW_PRESS)
		{
			if (!iter->second.isDown)
			{
				iter->second.pressedOnce = true;
				self->anyMouseButton.pressedOnce = true;

				iter->second.isDown = true;
				self->_anyMouseButtonCount++;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			if (iter->second.isDown)
			{
				iter->second.isDown = false;
				self->_anyMouseButtonCount--;
			}
		}

		if (self->_anyMouseButtonCount > 0)
		{ self->anyMouseButton.isDown = true; }
		else if (self->_anyMouseButtonCount == 0)
		{ self->anyMouseButton.isDown = false; }
		else
		{ Debug::LogWarning("InputManager::_anyMouseButtonCount is below 0."); }
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
