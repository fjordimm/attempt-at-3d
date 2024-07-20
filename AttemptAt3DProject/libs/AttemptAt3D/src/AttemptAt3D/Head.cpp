
#include "AttemptAt3D/Head.hpp"

#include <memory>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include "AttemptAt3D/(Debug)/Debug.hpp"
#include "AttemptAt3D/(Mesh)/Mesh.hpp"

namespace AttemptAt3D
{
	// TODO: delete
	static std::unique_ptr<AttemptAt3D::BodyReference> b1;
	static std::unique_ptr<AttemptAt3D::BodyReference> b2;

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
		glfwSetWindowSizeCallback(this->windowForGlfw, Head::onWindowResize);

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

			std::unique_ptr<Mesh> mesh1 = std::make_unique<Mesh>(verts1_s, std::move(verts1), elems1_s, std::move(elems1));

			// const float verts2_[] =
			// {
			// 	// X      Y      Z         R    G    B
			// 	-0.3f, +0.3f, +1.8f,     0.0f,1.0f,0.0f,
			// 	-0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
			// 	+0.3f, +0.3f, +1.8f,     0.0f,1.0f,0.0f,
			// 	+0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				
			// 	-0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
			// 	+0.0f, +0.0f, +1.0f,     0.0f,1.0f,0.0f,
			// 	+0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				
			// 	+0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
			// 	+0.0f, +0.0f, +1.0f,     0.0f,1.0f,0.0f,
			// 	+0.3f, +0.3f, +1.8f,     0.0f,1.0f,0.0f,
			// };
			// const std::size_t verts2_s = sizeof(verts2_) / sizeof(verts2_[0]);
			// std::unique_ptr<float[]> verts2(new float[verts2_s]);
			// std::memcpy(verts2.get(), verts2_, sizeof(verts2_));

			// const GLuint _elems2[] =
			// {
			// 	0, 1, 2,
			// 	3, 2, 1,

			// 	4, 5, 6,

			// 	7, 8, 9
			// };
			// const std::size_t elems2_s = sizeof(_elems2) / sizeof(_elems2[0]);
			// std::unique_ptr<GLuint[]> elems2(new GLuint[elems2_s]);
			// std::memcpy(elems2.get(), _elems2, sizeof(_elems2));

			b1 = this->bodyManager.addNewBody(this->shaderManager, std::move(mesh1));
			// b2 = this->bodyManager.addNewBody(this->shaderManager, verts2_s, std::move(verts2), elems2_s, std::move(elems2));
		}

		/* Miscellaneous Pre-Main-Loop Tasks */

		glfwSetWindowUserPointer(this->windowForGlfw, this); // passes a pointer to this Head to OpenGL
		this->_updateProjectionMatrix();

		/* Main Loop */

		this->mainLoop();
	}

	void Head::mainLoop()
	{
		while (!glfwWindowShouldClose(this->windowForGlfw))
		{
			/* Calculate Delta Time */

			float deltaTime = Head::calculateDeltaTime();

			/* Process inputs */

			/* Render everything */

			glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			this->bodyManager.drawAllBodies(this->shaderManager);

			/* Stuff required by GLFW */

			glfwPollEvents();
			glfwSwapBuffers(this->windowForGlfw);

			///////////////////

			{
				// static float cumlTime = 0.0f;
				// cumlTime += deltaTime;

				// {
				// 	glm::quat quatZ = glm::angleAxis(0.0006f * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
				// 	glm::mat4 rotZ = glm::toMat4(quatZ);

				// 	b1->access_bodyTransform() *= rotZ;
				// }

				// static bool alreadyDone = false;
				// if (!alreadyDone && cumlTime > 1000.0f)
				// {
				// 	alreadyDone = true;

				// 	const float verts2_[] =
				// 	{
				// 		// X      Y      Z         R    G    B
				// 		-0.3f, +0.3f, +1.8f,     0.0f,1.0f,0.0f,
				// 		-0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				// 		+0.3f, +0.3f, +1.8f,     0.0f,1.0f,0.0f,
				// 		+0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
						
				// 		-0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				// 		+0.0f, +0.0f, +1.0f,     0.0f,1.0f,0.0f,
				// 		+0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
						
				// 		+0.3f, -0.3f, +1.8f,     0.0f,1.0f,0.0f,
				// 		+0.0f, +0.0f, +1.0f,     0.0f,1.0f,0.0f,
				// 		+0.3f, +0.3f, +1.8f,     0.0f,1.0f,0.0f,
				// 	};
				// 	const std::size_t verts2_s = sizeof(verts2_) / sizeof(verts2_[0]);
				// 	std::unique_ptr<float[]> verts2(new float[verts2_s]);
				// 	std::memcpy(verts2.get(), verts2_, sizeof(verts2_));

				// 	const GLuint _elems2[] =
				// 	{
				// 		0, 1, 2,
				// 		3, 2, 1,

				// 		4, 5, 6,

				// 		7, 8, 9
				// 	};
				// 	const std::size_t elems2_s = sizeof(_elems2) / sizeof(_elems2[0]);
				// 	std::unique_ptr<GLuint[]> elems2(new GLuint[elems2_s]);
				// 	std::memcpy(elems2.get(), _elems2, sizeof(_elems2));

				// 	b2 = this->bodyManager.addNewBody(this->shaderManager, verts2_s, std::move(verts2), elems2_s, std::move(elems2));
				// }

				// if (b2)
				// {
				// 	glm::quat quatZ = glm::angleAxis(-0.0006f * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
				// 	glm::mat4 rotZ = glm::toMat4(quatZ);

				// 	b2->access_bodyTransform() *= rotZ;
				// }

				{
					// glm::quat quatX = glm::angleAxis(3.0f * cumlTime, glm::vec3(1.0f, 0.0f, 0.0f));
					// glm::mat4 rotX = glm::toMat4(quatX);

					// this->shaderManager.change_uni_sunRotVal(rotX);
				}
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

	void Head::onWindowResize(GLFWwindow* windowForGlfw, int width, int height)
	{
		Head* self = (Head*)glfwGetWindowUserPointer(windowForGlfw);

		glViewport(0, 0, width, height);

		self->change_aspectRatio((float)width / (float)height);
	}

	float Head::calculateDeltaTime()
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
}
