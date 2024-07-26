
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
#include "AttemptAt3D/(Form)/PhysicForm.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Head::Head() :
		windowForGlfw(nullptr),
		ptrForGlfw(),
		worldState()
	{}
	
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
		this->ptrForGlfw.add<InputManager>(&this->worldState.inputManager);

		/* OpenGL settings */

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		/* Activate shaders */

		this->worldState.shaderManager.compileAndActivateShaders();

		/* Head settings */

		glfwSetWindowSizeCallback(this->windowForGlfw, Head::onWindowResize);
		this->worldState.setFov(glm::radians(45.0f));
		this->worldState.setAspectRatio((float)windowWidth / (float)windowHeight);
		this->worldState.setNearClippingPlane(0.01f);
		this->worldState.setFarClippingPlane(100000.0f);

		this->worldState.inputManager.giveWindowForGlfw(this->windowForGlfw);

		this->worldState.mainCamera = Forms::Camera::New(this->worldState);
		this->worldState.mainCamera->tran.acqPosition() = Vec(0.0f, -1900.0f, 6.0f);
		this->worldState.mainCamera->recalculateAndApplyViewMatrix(this->worldState.shaderManager);

		/* Miscellaneous pre-main-loop tasks */

		worldState.hasCapturedCursorForCamera = false;
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
			WorldState::thingyCount = 0;

			long long seed = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
			std::default_random_engine randGen(seed);
			std::normal_distribution<float> randDist(0.0f, 3.0f);
			
			for (int i = 0; i < 5000; i++)
			{
				float xPos = randDist(randGen);
				float yPos = randDist(randGen);
				float zPos = randDist(randGen);

				Vec vec = Vec(xPos, yPos, zPos);
				vec *= glm::length2(vec);

				std::unique_ptr<PhysicForm> form1 = PhysicForm::New(this->worldState, MeshSamples::Cube().make());
				form1->tran.acqPosition() = vec;
				form1->velocity = -0.002f * vec;
				form1->friction = 0.001f;
				this->worldState.forms.push_back(std::move(form1));
				// std::unique_ptr<Form> form1 = Form::New(this->worldState, MeshSamples::Cube().make());
				// form1->tran.acqPosition() = vec;
				// this->worldState.forms.push_back(std::move(form1));
			}
		}
		////////////////////////////////////////////////////////////

		while (!glfwWindowShouldClose(this->windowForGlfw))
		{
			/* Stuff required by GLFW */

			glfwSwapBuffers(this->windowForGlfw);
			glfwPollEvents();

			/* Do movements, physics, inputs, etc. */

			float deltaTime;
			float totalTime;
			Head::CalculateDeltaTime(deltaTime, totalTime);

			this->doCameraMovements(deltaTime);
			this->worldState.mainCamera->onUpdate(this->worldState, deltaTime);

			for (std::unique_ptr<Form>& _form : this->worldState.forms)
			{
				Form* form = _form.get();
				form->onUpdate(this->worldState, deltaTime);
			}

			/// Temp ///
			////////////////////////////////////////////////////////////
			static float timeCounter = 0.0f;
			static float frameCounter = 0.0f;
			timeCounter += deltaTime;
			frameCounter += 1.0f;

			if (timeCounter >= 1500.0f)
			{
				Debug::Logf("fps: %f", frameCounter / (timeCounter / 1000.0f));

				timeCounter = 0.0f;
				frameCounter = 0.0f;
			}
			////////////////////////////////////////////////////////////

			/* Render everything */

			glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (std::unique_ptr<Form>& _form : this->worldState.forms)
			{
				Form* form = _form.get();
				form->draw(this->worldState.shaderManager);
			}

			/* Required by InputManager at the end of each iteration of the main loop */

			this->worldState.inputManager.nextLoopIteration();
		}

		this->endGlfw();
	}

	void Head::endGlfw()
	{
		this->worldState.shaderManager.cleanupForGl();
		glfwTerminate();
	}
	
	void Head::doCameraMovements(float deltaTime)
	{
		if (this->worldState.inputManager.getAnyMouseButton().pressedOnce)
		{
			this->worldState.hasCapturedCursorForCamera = true;
			glfwSetInputMode(this->windowForGlfw, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		if (this->worldState.inputManager.findKey(GLFW_KEY_ESCAPE).pressedOnce)
		{
			this->worldState.hasCapturedCursorForCamera = false;
			glfwSetInputMode(this->windowForGlfw, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		this->worldState.mainCameraMovementSpeed += 0.3f * this->worldState.mainCameraMovementSpeed * this->worldState.inputManager.getDeltaScrollY();
		if (this->worldState.mainCameraMovementSpeed < 0.000002f)
		{ this->worldState.mainCameraMovementSpeed = 0.000002f; }

		float cameraMovementSpeed = this->worldState.mainCameraMovementSpeed;
		float cameraRotationSpeed = this->worldState.mainCameraRotationSpeed;

		/* Camera translation */

		Vec movement = Vecs::Zero;
		if (this->worldState.inputManager.findKey(GLFW_KEY_W).isDown)
		{
			Vec temp = glm::normalize(Vec(this->worldState.mainCamera->tran.getForwardVec().x, this->worldState.mainCamera->tran.getForwardVec().y, 0.0f));
			movement.x += temp.x;
			movement.y += temp.y;
		}
		if (this->worldState.inputManager.findKey(GLFW_KEY_S).isDown)
		{
			Vec temp = glm::normalize(Vec(this->worldState.mainCamera->tran.getForwardVec().x, this->worldState.mainCamera->tran.getForwardVec().y, 0.0f));
			movement.x -= temp.x;
			movement.y -= temp.y;
		}
		if (this->worldState.inputManager.findKey(GLFW_KEY_D).isDown)
		{
			Vec temp = glm::normalize(Vec(this->worldState.mainCamera->tran.getRightVec().x, this->worldState.mainCamera->tran.getRightVec().y, 0.0f));
			movement.x += temp.x;
			movement.y += temp.y;
		}
		if (this->worldState.inputManager.findKey(GLFW_KEY_A).isDown)
		{
			Vec temp = glm::normalize(Vec(this->worldState.mainCamera->tran.getRightVec().x, this->worldState.mainCamera->tran.getRightVec().y, 0.0f));
			movement.x -= temp.x;
			movement.y -= temp.y;
		}
		if (this->worldState.inputManager.findKey(GLFW_KEY_SPACE).isDown)
		{
			movement.z += 1.0f;
		}
		if (this->worldState.inputManager.findKey(GLFW_KEY_LEFT_SHIFT).isDown)
		{
			movement.z -= 1.0f;
		}
		if (!Vecs::RoughlyEqual(movement, Vecs::Zero))
		{
			// this->worldState.mainCamera->tran.move((cameraMovementSpeed * deltaTime) * glm::normalize(movement));
			this->worldState.mainCamera->velocity += (cameraMovementSpeed * deltaTime ) * glm::normalize(movement);
		}

		/* Camera rotation */

		if (this->worldState.hasCapturedCursorForCamera)
		{
			float deltaCursorX = this->worldState.inputManager.getDeltaCursorX();
			float deltaCursorY = this->worldState.inputManager.getDeltaCursorY();

			if (!Math::RoughlyEqual(deltaCursorX, 0.0f) || !Math::RoughlyEqual(deltaCursorY, 0.0f))
			{
				// Debug::Logf("(%f, %f)", deltaCursorX, deltaCursorY);

				glm::vec2 temp = glm::vec2(deltaCursorX, deltaCursorY);
				this->worldState.mainCamera->tran.locallyRotate(Vecs::Right, -temp.y * cameraRotationSpeed);
				this->worldState.mainCamera->tran.rotate(Vecs::Up, -temp.x * cameraRotationSpeed);
			}
		}
		{
			/* Bound camera rotation from looking beyond straight up or straight down */

			Vec eulers = this->worldState.mainCamera->tran.eulerAngles();
			static constexpr float maxAngle = Math::PiOver2 - 0.01f;
			if (eulers.x > maxAngle)
			{
				this->worldState.mainCamera->tran.locallyRotate(Vecs::Right, -(eulers.x - maxAngle));
			}
			else if (eulers.x < -maxAngle)
			{
				this->worldState.mainCamera->tran.locallyRotate(Vecs::Right, (-maxAngle - eulers.x));
			}
		}

		/* Update view matrix */

		this->worldState.mainCamera->recalculateAndApplyViewMatrix(this->worldState.shaderManager);
	}

	/* Functions */

	void Head::CalculateDeltaTime(float& deltaTime, float& totalTime)
	{
		using std::chrono::steady_clock;
		using std::chrono::duration;
		using durMillisecs = duration<float, std::ratio<1, 1000>>;

		static steady_clock::time_point initialTimePoint = steady_clock::now();

		static steady_clock::time_point timePoint = steady_clock::now();
		steady_clock::time_point oldTimePoint = timePoint;
		timePoint = steady_clock::now();
		durMillisecs timeElapsedSinceLastFrame = std::chrono::duration_cast<durMillisecs>(timePoint - oldTimePoint);
		deltaTime = timeElapsedSinceLastFrame.count();

		durMillisecs timeElapsedSinceStart = std::chrono::duration_cast<durMillisecs>(timePoint - initialTimePoint);
		totalTime = timeElapsedSinceStart.count();
	}

	/* Methods for External Use */

	void Head::onWindowResize(GLFWwindow* windowForGlfw, int width, int height)
	{
		Head* self = PtrForGlfw::Retrieve(windowForGlfw)->get<Head>();

		glViewport(0, 0, width, height);
		self->worldState.setAspectRatio((float)width / (float)height);
	}
}
