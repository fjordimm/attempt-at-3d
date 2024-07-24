
#pragma once

#include <map>
#include <cstdlib>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AttemptAt3D
{
	class InputManager
	{
		/* Structs */

	   public:
		struct InputVal
		{
		   public:
			bool isDown;
			bool pressedOnce;

			InputVal() :
				isDown(false),
				pressedOnce(false)
			{}

			InputVal(bool isDown, bool pressedOnce) :
				isDown(isDown),
				pressedOnce(pressedOnce)
			{}

			InputVal(const InputVal& that) : InputVal(that.isDown, that.pressedOnce) {}

			InputVal& operator=(const InputVal& that)
			{
				this->isDown = that.isDown;
				this->pressedOnce = that.pressedOnce;
				return *this;
			}
		};

		/* Constructors */

	   public:
		InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;
		
		InputManager();
		
		/* Fields */

	   private:
		std::map<int, InputVal> keyDict;
		InputVal anyKey;
		int _anyKeyCount;

		std::map<int, InputVal> mouseButtonDict;
		InputVal anyMouseButton;
		int _anyMouseButtonCount;

		float cursorX;
		float cursorY;
		float deltaCursorX;
		float deltaCursorY;

		/* Getters and Setters */

	   public:
		inline const InputVal& get_anyKey() { return this->anyKey; }
		inline const InputVal& get_anyMouseButton() { return this->anyMouseButton; }
		inline float get_cursorX() { return this->cursorX; }
		inline float get_cursorY() { return this->cursorY; }
		inline float get_deltaCursorX() { return this->deltaCursorX; }
		inline float get_deltaCursorY() { return this->deltaCursorY; }

		/* Methods */

	   public:
		void giveWindowForGlfw(GLFWwindow* windowForGlfw);
		void nextLoopIteration();

		const InputVal& getKey(int key) const;
		const InputVal& getMouseButton(int mouseButton) const;

		/* Methods for External Use */

	   private:
		static void keyCallback(GLFWwindow* windowForGlfw, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* windowForGlfw, int button, int action, int mods);
		static void cursorPosCallback(GLFWwindow* windowForGlfw, double xPos, double yPos);
	};
}
