
#pragma once

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"
#include "AttemptAt3D/(PtrForGlfw)/PtrForGlfw.hpp"
#include "AttemptAt3D/(ShaderManager)/ShaderManager.hpp"
#include "AttemptAt3D/(InputManager)/InputManager.hpp"
#include "AttemptAt3D/(Form)/Form.hpp"
#include "AttemptAt3D/(Form)/Forms/Camera.hpp"

namespace AttemptAt3D
{
	class Head
	{
		/* Constructors */

	   public:
		Head(const Head&) = delete;
		Head& operator=(const Head&) = delete;

		Head();

		/* Fields */

	   private:
		GLFWwindow* windowForGlfw;
		PtrForGlfw ptrForGlfw;
		float _fov;
		float _aspectRatio;
		float _nearClippingPlane;
		float _farClippingPlane;

		ShaderManager shaderManager;
		InputManager inputManager;

		bool capturedMouseForCamera;

		std::unique_ptr<Forms::Camera> mainCamera;

		/* Getters and Setters */

	   public:
		inline ShaderManager& get_shaderManager() { return this->shaderManager; }

	   private:
		void set_fov(float val);
		void set_aspectRatio(float val);
		void set_nearClippingPlane(float val);
		void set_farClippingPlane(float val);

		/* Methods */

	   public:
		void start(int windowWidth = 600, int windowHeight = 600, const std::string windowTitle = "Placeholder Window Title");
	
	   private:
		void mainLoop();
		void endGlfw();
		void _updateProjectionMatrix();

		void doCameraMovements(float deltaTime);

		/* Functions */

	   private:
		static float CalculateDeltaTime(); // In milliseconds

		/* Methods for External Use */

	   private:
		static void onWindowResize(GLFWwindow* windowForGlfw, int width, int height);
	};
}
