
#pragma once

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"
#include "AttemptAt3D/(ShaderManager)/ShaderManager.hpp"
#include "AttemptAt3D/(Form)/Form.hpp"

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
		float _fov;
		float _aspectRatio;
		float _nearClippingPlane;
		float _farClippingPlane;

		ShaderManager shaderManager;

		// std::unique_ptr<Form> theSun;

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

		/* Functions */

	   private:
		static float CalculateDeltaTime(); // In milliseconds

		/* Methods for External Use */

	   public:
		static void onWindowResize(GLFWwindow* windowForGlfw, int width, int height);
	};
}
