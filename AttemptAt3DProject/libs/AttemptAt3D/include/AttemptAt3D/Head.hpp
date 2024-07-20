
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include "AttemptAt3D/BodyManager/BodyManager.hpp"
#include "AttemptAt3D/ShaderManager/ShaderManager.hpp"

namespace AttemptAt3D
{
	class Head
	{
		/* Fields */

	   private:
		GLFWwindow* windowForGlfw;
		float _fov;
		float _aspectRatio;
		float _nearClippingPlane;
		float _farClippingPlane;

		ShaderManager shaderManager;
		BodyManager bodyManager;

		/* Getters and Setters */

	   public:
		inline ShaderManager& get_shaderManager() { return this->shaderManager; }
		inline BodyManager& get_bodyManager() { return this->bodyManager; }

	   private:
		void change_fov(float val);
		void change_aspectRatio(float val);
		void change_nearClippingPlane(float val);
		void change_farClippingPlane(float val);

		/* Constructors */

	   public:
		Head(const Head&) = delete;
		Head& operator=(const Head&) = delete;

		Head();

		/* Methods */

	   public:
		void start(int windowWidth = 600, int windowHeight = 600, const std::string windowTitle = "Placeholder Window Title");
	
	   private:
		void mainLoop();
		void endGlfw();
		void _updateProjectionMatrix();

		/* Methods for External Use */

	   public:
		static void onWindowResize(GLFWwindow* windowForGlfw, int width, int height);
		static float calculateDeltaTime(); // In nanoseconds
	};
}
