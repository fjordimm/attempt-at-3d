
#include "AttemptAt3D/Head.hpp"

#include <memory>
#include <cstring>
#include "AttemptAt3D/Debug/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Head::Head() :
		windowForGlfw(nullptr),
		_fov(glm::radians(45.0f)),
		_aspectRatio(1.0f),
		_nearClippingPlane(0.1f),
		_farClippingPlane(100000.0f),
		shaderManager(),
		bodyManager()
	{}

	void Head::change_fov(float val)
	{
		this->_fov = val;
		this->updateProjectionMatrix();
	}

	void Head::change_aspectRatio(float val)
	{
		this->_aspectRatio = val;
		this->updateProjectionMatrix();
	}

	void Head::change_nearClippingPlane(float val)
	{
		this->_nearClippingPlane = val;
		this->updateProjectionMatrix();
	}

	void Head::change_farClippingPlane(float val)
	{
		this->_farClippingPlane = val;
		this->updateProjectionMatrix();
	}
	
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
		glfwSetWindowSizeCallback(this->windowForGlfw, onWindowResize);

		/* Activate Shaders */

		this->shaderManager.compileAndActivateShaders();

		/* Test vertices */

		{
			const float verts1_[] =
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
			const std::size_t verts1_s = sizeof(verts1_) / sizeof(verts1_[0]);
			std::unique_ptr<float[]> verts1(new float[verts1_s]);
			std::memcpy(verts1.get(), verts1_, sizeof(verts1_));

			const GLuint elems1_[] =
			{
				0, 1, 2,
				3, 2, 1,

				4, 5, 6,

				7, 8, 9
			};
			const std::size_t elems1_s = sizeof(elems1_) / sizeof(elems1_[0]);
			std::unique_ptr<GLuint[]> elems1(new GLuint[elems1_s]);
			std::memcpy(elems1.get(), elems1_, sizeof(elems1_));


			///////////////////

			const float verts2_[] =
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
			const std::size_t verts2_s = sizeof(verts2_) / sizeof(verts2_[0]);
			std::unique_ptr<float[]> verts2(new float[verts2_s]);
			std::memcpy(verts2.get(), verts2_, sizeof(verts2_));

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

			auto b1 = this->bodyManager.addNewBody(this->shaderManager, verts1_s, std::move(verts1), elems1_s, std::move(elems1));
			auto b2 = this->bodyManager.addNewBody(this->shaderManager, verts2_s, std::move(verts2), elems2_s, std::move(elems2));
		}

		/* Miscellaneous Pre-Main-Loop Tasks */

		glfwSetWindowUserPointer(this->windowForGlfw, this);
		this->updateProjectionMatrix();

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

			this->bodyManager.drawAllBodies();

			/* Stuff required by GLFW */

			glfwPollEvents();
			glfwSwapBuffers(this->windowForGlfw);



			// this->shaderManager.change_uni_viewVal(glm::lookAt(glm::vec3(0.0f, -9.0f, 9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		}

		this->endGlfw();
	}

	void Head::endGlfw()
	{
		this->shaderManager.cleanupForGl();
		this->bodyManager.cleanupForGl();
		glfwTerminate();
	}

	void Head::updateProjectionMatrix()
	{
		this->shaderManager.change_uni_projVal(
			glm::perspective(this->_fov, this->_aspectRatio, this->_nearClippingPlane, this->_farClippingPlane)
		);
	}

	void Head::onWindowResize(GLFWwindow* windowForGlfw, int width, int height)
	{
		Head* self = (Head*)glfwGetWindowUserPointer(windowForGlfw);

		glViewport(0, 0, width, height);

		self->change_aspectRatio((float)width / (float)height);
	}
}
