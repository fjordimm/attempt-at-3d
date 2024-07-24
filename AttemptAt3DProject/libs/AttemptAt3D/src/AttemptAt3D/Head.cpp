
#include "AttemptAt3D/Head.hpp"

#include <cstring>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <random>
#include "AttemptAt3D/(Debug)/Debug.hpp"
#include "AttemptAt3D/(Tran)/Tran.hpp"
#include "AttemptAt3D/(headerGroups)/allMeshSamples.hpp"
#include "AttemptAt3D/(Math)/Math.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Head::Head() :
		windowForGlfw(nullptr),
		ptrForGlfw(),
		shaderManager(),
		inputManager(),
		forms()
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

		/* Head settings */

		glfwSetWindowSizeCallback(this->windowForGlfw, Head::onWindowResize);
		this->set_fov(glm::radians(45.0f));
		this->set_aspectRatio((float)windowWidth / (float)windowHeight);
		this->set_nearClippingPlane(0.01f);
		this->set_farClippingPlane(100000.0f);

		this->inputManager.giveWindowForGlfw(this->windowForGlfw);

		this->mainCamera->tran.acq_position() = Vec(0.0f, -21.0f, 6.0f);
		this->mainCamera->recalculateAndApplyViewMatrix(this->shaderManager);

		/* Miscellaneous pre-main-loop tasks */

		capturedMouseForCamera = false;
		glfwSetInputMode(this->windowForGlfw, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		
		if (glfwRawMouseMotionSupported())
		{ glfwSetInputMode(this->windowForGlfw, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE); }
		else
		{ Debug::LogFatalError("Machine does not support raw mouse motion."); }

		/* Main loop */

		this->mainLoop();
	}

	void Head::mainLoop()
	{
		/// Temp ///
		////////////////////////////////////////////////////////////
		{
			long long seed = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
			std::default_random_engine randGen(seed);
			std::normal_distribution<float> randDist(-50.0f, 50.0f);
			
			for (int i = 0; i < 6000; i++)
			{
				float xPos = randDist(randGen);
				float yPos = randDist(randGen);
				float zPos = randDist(randGen);

				std::unique_ptr<Form> form = std::make_unique<Form>(this->shaderManager, MeshSamples::Cube().make());
				form->tran.acq_position() = Vec(xPos, yPos, zPos);
				this->forms.push_back(std::move(form));
			}
		}
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
			// form2->tran.rotate(Vecs::Forwards, 0.001f * deltaTime);
			////////////////////////////////////////////////////////////

			/* Render everything */

			glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (std::unique_ptr<Form>& _form : this->forms)
			{
				Form* form = _form.get();
				form->draw(this->shaderManager);
			}

			/* Required by InputManager at the end of each iteration of the main loop */

			this->inputManager.nextLoopIteration();
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
		if (this->inputManager.get_anyMouseButton().pressedOnce)
		{
			capturedMouseForCamera = true;
			glfwSetInputMode(this->windowForGlfw, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		if (this->inputManager.getKey(GLFW_KEY_ESCAPE).pressedOnce)
		{
			capturedMouseForCamera = false;
			glfwSetInputMode(this->windowForGlfw, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		bool hasMadeMovements = false;

		float moveSpeed = 0.15f;
		if (this->inputManager.getKey(GLFW_KEY_LEFT_CONTROL).isDown)
		{ moveSpeed *= 0.1f; }
		float rotSpeed = 0.004f;

		/* Camera translation */

		Vec movement = Vecs::Zero;
		if (this->inputManager.getKey(GLFW_KEY_W).isDown)
		{
			Vec temp = glm::normalize(Vec(this->mainCamera->tran.get_forwardVec().x, this->mainCamera->tran.get_forwardVec().y, 0.0f));
			movement.x += temp.x;
			movement.y += temp.y;
		}
		if (this->inputManager.getKey(GLFW_KEY_S).isDown)
		{
			Vec temp = glm::normalize(Vec(this->mainCamera->tran.get_forwardVec().x, this->mainCamera->tran.get_forwardVec().y, 0.0f));
			movement.x -= temp.x;
			movement.y -= temp.y;
		}
		if (this->inputManager.getKey(GLFW_KEY_D).isDown)
		{
			Vec temp = glm::normalize(Vec(this->mainCamera->tran.get_rightVec().x, this->mainCamera->tran.get_rightVec().y, 0.0f));
			movement.x += temp.x;
			movement.y += temp.y;
		}
		if (this->inputManager.getKey(GLFW_KEY_A).isDown)
		{
			Vec temp = glm::normalize(Vec(this->mainCamera->tran.get_rightVec().x, this->mainCamera->tran.get_rightVec().y, 0.0f));
			movement.x -= temp.x;
			movement.y -= temp.y;
		}
		if (this->inputManager.getKey(GLFW_KEY_SPACE).isDown)
		{
			movement.z += 1.0f;
		}
		if (this->inputManager.getKey(GLFW_KEY_LEFT_SHIFT).isDown)
		{
			movement.z -= 1.0f;
		}
		if (!Vecs::RoughlyEqual(movement, Vecs::Zero))
		{
			this->mainCamera->tran.move((moveSpeed * deltaTime) * glm::normalize(movement));
			hasMadeMovements = true;
		}

		/* Camera rotation */

		if (this->capturedMouseForCamera)
		{
			float deltaCursorX = this->inputManager.getDeltaCursorX();
			float deltaCursorY = this->inputManager.getDeltaCursorY();

			if (!Math::RoughlyEqual(deltaCursorX, 0.0f) || !Math::RoughlyEqual(deltaCursorY, 0.0f))
			{
				// Debug::Logf("(%f, %f)", deltaCursorX, deltaCursorY);

				glm::vec2 temp = glm::vec2(deltaCursorX, deltaCursorY);
				this->mainCamera->tran.locallyRotate(Vecs::Right, -temp.y * rotSpeed);
				this->mainCamera->tran.rotate(Vecs::Up, -temp.x * rotSpeed);

				hasMadeMovements = true;
			}
		}
		{
			/* Bound camera rotation from looking beyond straight up or straight down */

			Vec eulers = this->mainCamera->tran.getEulerAngles();
			static constexpr float maxAngle = Math::PiOver2 - 0.01f;
			if (eulers.x > maxAngle)
			{
				this->mainCamera->tran.locallyRotate(Vecs::Right, -(eulers.x - maxAngle));
				hasMadeMovements = true;
			}
			else if (eulers.x < -maxAngle)
			{
				this->mainCamera->tran.locallyRotate(Vecs::Right, (-maxAngle - eulers.x));
				hasMadeMovements = true;
			}
		}

		/* Update view matrix if necessary */

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
