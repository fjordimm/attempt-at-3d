
#include "AttemptAt3D/Head.hpp"

#include <memory>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include "AttemptAt3D/(Debug)/Debug.hpp"
#include "AttemptAt3D/(Tran)/Tran.hpp"
#include "AttemptAt3D/(headerGroups)/allMeshSamples.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Head::Head() :
		windowForGlfw(nullptr),
		ptrForGlfw(),
		shaderManager(),
		inputManager()
	{
		this->mainCamera = std::make_unique<Forms::Camera>(this->shaderManager);
	}

	void Head::set_fov(float val)
	{
		this->_fov = val;
		this->_updateProjectionMatrix();
	}

	void Head::set_aspectRatio(float val)
	{
		this->_aspectRatio = val;
		this->_updateProjectionMatrix();
	}

	void Head::set_nearClippingPlane(float val)
	{
		this->_nearClippingPlane = val;
		this->_updateProjectionMatrix();
	}

	void Head::set_farClippingPlane(float val)
	{
		this->_farClippingPlane = val;
		this->_updateProjectionMatrix();
	}
	
	/* Methods */

	void Head::start(int windowWidth, int windowHeight, const std::string windowTitle)
	{
		/* Create the window, initializing GLFW and GLEW */

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

		/* Bind class instances to the GLFW user pointer */

		this->ptrForGlfw.bindToGlfwWindow(this->windowForGlfw);
		this->ptrForGlfw.add<Head>(this);
		this->ptrForGlfw.add<InputManager>(&this->inputManager);

		/* OpenGL settings */

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		/* Activate shaders */

		this->shaderManager.compileAndActivateShaders();

		/* Miscellaneous pre-main-loop tasks */

		glfwSetWindowSizeCallback(this->windowForGlfw, Head::onWindowResize);
		this->set_fov(glm::radians(45.0f));
		this->set_aspectRatio((float)windowWidth / (float)windowHeight);
		this->set_nearClippingPlane(0.01f);
		this->set_farClippingPlane(100000.0f);

		this->inputManager.setKeyCallbackForGlfw(this->windowForGlfw);

		/* Main loop */

		this->mainLoop();
	}

	void Head::mainLoop()
	{
		/// Temp ///
		////////////////////////////////////////////////////////////
		float totalTime = 0.0f;

		this->mainCamera->tran.acq_position() = Vec(0.0f, -21.0f, 6.0f);
		this->mainCamera->recalculateAndApplyViewMatrix(this->shaderManager);

		std::unique_ptr<Form> form1 = std::make_unique<Form>(this->shaderManager, MeshSamples::Cube().make());
		form1->tran.acq_scale().x = 3.0f;
		form1->tran.acq_scale().y = 3.0f;
		form1->tran.acq_scale().z = 0.1f;

		std::unique_ptr<Form> form2 = std::make_unique<Form>(this->shaderManager, MeshSamples::Cube().make());
		form2->tran.acq_position().z = 1.1f;
		form2->tran.locallyRotate(Vecs::Up, -0.25f * 3.1415926f);
		// form2->tran.locallyRotate(Vecs::Right, -0.0f * 3.1415926f);
		// form2->tran.locallyRotate(Vecs::Forwards, 0.0f * 3.1415926f);
		////////////////////////////////////////////////////////////

		while (!glfwWindowShouldClose(this->windowForGlfw))
		{
			/* Stuff required by GLFW */

			glfwSwapBuffers(this->windowForGlfw);
			glfwPollEvents();

			/* Do movements, physics, inputs, etc. */

			float deltaTime = Head::CalculateDeltaTime();

			this->doCameraMovements(deltaTime);

			/// Temp ///
			////////////////////////////////////////////////////////////
			totalTime += deltaTime;

			form2->tran.rotate(Vecs::Forwards, 0.001f * deltaTime);
			////////////////////////////////////////////////////////////

			/* Render everything */

			glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// draw all bodies
			form1->draw(this->shaderManager);
			form2->draw(this->shaderManager);
		}

		this->endGlfw();
	}

	void Head::endGlfw()
	{
		this->shaderManager.cleanupForGl();
		glfwTerminate();
	}

	void Head::_updateProjectionMatrix()
	{
		this->shaderManager.set_uni_projVal(
			glm::perspective(this->_fov, this->_aspectRatio, this->_nearClippingPlane, this->_farClippingPlane)
		);
	}
	
	void Head::doCameraMovements(float deltaTime)
	{
		bool hasMadeMovements = false;

		if (this->inputManager[GLFW_KEY_W])
		{
			this->mainCamera->tran.locallyMove((0.01f * deltaTime) * Vecs::Forwards);
			hasMadeMovements = true;
		}
		else if (this->inputManager[GLFW_KEY_S])
		{
			this->mainCamera->tran.locallyMove((-0.01f * deltaTime) * Vecs::Forwards);
			hasMadeMovements = true;
		}

		if (hasMadeMovements)
		{
			this->mainCamera->recalculateAndApplyViewMatrix(this->shaderManager);
		}
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
		Head* self = PtrForGlfw::Retrieve(windowForGlfw)->get<Head>();

		glViewport(0, 0, width, height);
		self->set_aspectRatio((float)width / (float)height);
	}
}
