
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
			float verts1[] =
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

			GLuint elems1[] =
			{
				0, 1, 2,
				3, 2, 1,

				4, 5, 6,

				7, 8, 9
			};

			auto b = this->bodyManager.addNewBody(60, std::unique_ptr<float[]>(verts1), 12, std::unique_ptr<GLuint[]>(elems1));
		}

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
		this->bodyManager.cleanup();
	}
}