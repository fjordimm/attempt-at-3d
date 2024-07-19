
#include <memory>
#include <cstring>
#include "AttemptAt3D/Head.hpp"
#include "AttemptAt3D/Debug/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Head::Head() :
		windowForGlfw(nullptr),
		shaderManager(),
		bodyManager()
	{}
	
	/* Methods */

	void Head::start(int windowWidth, int windowHeight, const std::string windowTitle)
	{
		/* Create the window, initializing GLFW and GLEW */

		// Initializes this->windowForGlfw
		{
			if (!glfwInit())
			{ Debug::LogFatalError("glfwInit failed."); }

			// Window hints
			glfwWindowHint(GLFW_SAMPLES, 5); // anti-aliasing

			this->windowForGlfw = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
			if (!this->windowForGlfw)
			{
				glfwTerminate();
				Debug::LogFatalError("glfwCreateWindow failed.");
			}

			glfwMakeContextCurrent(this->windowForGlfw);

			glewExperimental = GL_TRUE;
			glewInit();
		}

		/* OpenGL Settings */

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		/* Test vertices */

		{
			const float _verts1[] =
			{
				// X      Y      Z         R    G    B
				-0.3f, +0.3f, +0.8f,     1.0f,0.0f,0.0f,
				-0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
				+0.3f, +0.3f, +0.8f,     1.0f,0.0f,0.0f,
				+0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
				
				-0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
				+0.0f, +0.0f, +0.0f,     1.0f,0.0f,0.0f,
				+0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
				
				+0.3f, -0.3f, +0.8f,     1.0f,0.0f,0.0f,
				+0.0f, +0.0f, +0.0f,     1.0f,0.0f,0.0f,
				+0.3f, +0.3f, +0.8f,     1.0f,0.0f,0.0f,
			};
			const std::size_t verts1_s = sizeof(_verts1) / sizeof(_verts1[0]);
			std::unique_ptr<float[]> verts1(new float[verts1_s]);
			std::memcpy(verts1.get(), _verts1, sizeof(_verts1));

			const GLuint _elems1[] =
			{
				0, 1, 2,
				3, 2, 1,

				4, 5, 6,

				7, 8, 9
			};
			const std::size_t elems1_s = sizeof(_elems1) / sizeof(_elems1[0]);
			std::unique_ptr<GLuint[]> elems1(new GLuint[elems1_s]);
			std::memcpy(elems1.get(), _elems1, sizeof(_elems1));


			///////////////////

			const float _verts2[] =
			{
				// X      Y      Z         R    G    B
				-0.3f, +0.3f, +1.8f,     0.0f,1.0f,0.0f,
				-0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				+0.3f, +0.3f, +1.8f,     0.0f,1.0f,0.0f,
				+0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				
				-0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				+0.0f, +0.0f, +1.0f,     0.0f,1.0f,0.0f,
				+0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				
				+0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				+0.0f, +0.0f, +1.0f,     0.0f,1.0f,0.0f,
				+0.3f, +0.3f, +1.8f,     0.0f,1.0f,0.0f,
			};
			const std::size_t verts2_s = sizeof(_verts2) / sizeof(_verts2[0]);
			std::unique_ptr<float[]> verts2(new float[verts2_s]);
			std::memcpy(verts2.get(), _verts2, sizeof(_verts2));

			const GLuint _elems2[] =
			{
				0, 1, 2,
				3, 2, 1,

				4, 5, 6,

				7, 8, 9
			};
			const std::size_t elems2_s = sizeof(_elems2) / sizeof(_elems2[0]);
			std::unique_ptr<GLuint[]> elems2(new GLuint[elems2_s]);
			std::memcpy(elems2.get(), _elems2, sizeof(_elems2));

			auto b1 = this->bodyManager.addNewBody(verts1_s, std::move(verts1), elems1_s, std::move(elems1));
			auto b2 = this->bodyManager.addNewBody(verts2_s, std::move(verts2), elems2_s, std::move(elems2));
		}

		/* Activate Shaders */

		this->shaderManager.compileAndActivateShaders();

		/* Main Loop */

		this->mainLoop();
	}

	void Head::mainLoop()
	{
		while (!glfwWindowShouldClose(this->windowForGlfw))
		{
			/* Process inputs */

			/* Render everything */

			glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			this->bodyManager.drawAllBodies(this->shaderManager);

			/* Adjust the canvas when the window is resized */

			glfwSetWindowSizeCallback(this->windowForGlfw, [](GLFWwindow* _window, int _width, int _height)
			{ glViewport(0, 0, _width, _height); });

			/* Stuff required by GLFW */

			glfwPollEvents();
			glfwSwapBuffers(this->windowForGlfw);
		}

		this->endGlfw();
	}

	void Head::endGlfw()
	{
		this->shaderManager.cleanupForGl();
		this->bodyManager.cleanupForGl();
		glfwTerminate();
	}
}