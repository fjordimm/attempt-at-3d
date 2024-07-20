
#include "AttemptAt3D/Head.hpp"

#include <memory>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include "AttemptAt3D/(Debug)/Debug.hpp"
#include "AttemptAt3D/(Mesh)/Mesh.hpp"
#include "AttemptAt3D/(Mesh)/MeshSamples/InvertedPyramid.hpp"

namespace AttemptAt3D
{
	// TODO: delete
	static std::unique_ptr<AttemptAt3D::BodyReference> b1;
	static std::unique_ptr<AttemptAt3D::BodyReference> b2;
	static std::unique_ptr<AttemptAt3D::BodyReference> b3;

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
		this->_updateProjectionMatrix();
	}

	void Head::change_aspectRatio(float val)
	{
		this->_aspectRatio = val;
		this->_updateProjectionMatrix();
	}

	void Head::change_nearClippingPlane(float val)
	{
		this->_nearClippingPlane = val;
		this->_updateProjectionMatrix();
	}

	void Head::change_farClippingPlane(float val)
	{
		this->_farClippingPlane = val;
		this->_updateProjectionMatrix();
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
			glfwWindowHint(GLFW_SAMPLES, 7); // anti-aliasing

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
		glfwSetWindowSizeCallback(this->windowForGlfw, Head::onWindowResize);

		/* Activate Shaders */

		this->shaderManager.compileAndActivateShaders();

		/* Miscellaneous Pre-Main-Loop Tasks */

		glfwSetWindowUserPointer(this->windowForGlfw, this); // passes a pointer to this Head to OpenGL
		this->_updateProjectionMatrix();

		/* test objects */

		b1 = this->bodyManager.addNewBody(this->shaderManager, MeshSamples::InvertedPyramid().make());

		b2 = this->bodyManager.addNewBody(this->shaderManager, MeshSamples::InvertedPyramid().make());
		b2->access_bodyTransform() = glm::translate(b2->access_bodyTransform(), glm::vec3(-1.4f, 0.0f, 0.0f));

		b3 = this->bodyManager.addNewBody(this->shaderManager, MeshSamples::InvertedPyramid().make());
		b3->access_bodyTransform() = glm::translate(b3->access_bodyTransform(), glm::vec3(1.4f, 0.0f, 0.0f));

		/* Main Loop */

		this->mainLoop();
	}

	void Head::mainLoop()
	{
		while (!glfwWindowShouldClose(this->windowForGlfw))
		{
			/* Calculate Delta Time */

			float deltaTime = Head::CalculateDeltaTime();

			/* Process inputs */

			/* Render everything */

			glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			this->bodyManager.drawAllBodies(this->shaderManager);

			/* Stuff required by GLFW */

			glfwPollEvents();
			glfwSwapBuffers(this->windowForGlfw);

			///////////////

			{
				glm::mat4 rot = glm::toMat4(glm::angleAxis(-0.0002f * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f)));
				b2->access_bodyTransform() *= rot;
			}

			{
				glm::mat4 rot = glm::toMat4(glm::angleAxis(-0.0004f * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f)));
				b1->access_bodyTransform() *= rot;
			}

			{
				glm::mat4 rot = glm::toMat4(glm::angleAxis(-0.0008f * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f)));
				b3->access_bodyTransform() *= rot;
			}
		}

		this->endGlfw();
	}

	void Head::endGlfw()
	{
		this->shaderManager.cleanupForGl();
		this->bodyManager.cleanupForGl();
		glfwTerminate();
	}

	void Head::_updateProjectionMatrix()
	{
		this->shaderManager.change_uni_projVal(
			glm::perspective(this->_fov, this->_aspectRatio, this->_nearClippingPlane, this->_farClippingPlane)
		);
	}

	/* Functions */

	float Head::CalculateDeltaTime()
	{
		using std::chrono::steady_clock;
		using std::chrono::duration;
		using durMillisecs = duration<float, std::ratio<1, 1000>>;

		static steady_clock::time_point timePoint = steady_clock::now();
		steady_clock::time_point oldTimePoint = timePoint;
		timePoint = steady_clock::now();

		durMillisecs timeElapsed = std::chrono::duration_cast<durMillisecs>(timePoint - oldTimePoint);
		return timeElapsed.count();
	}

	/* Methods for External Use */

	void Head::onWindowResize(GLFWwindow* windowForGlfw, int width, int height)
	{
		Head* self = (Head*)glfwGetWindowUserPointer(windowForGlfw);

		glViewport(0, 0, width, height);

		self->change_aspectRatio((float)width / (float)height);
	}
}
