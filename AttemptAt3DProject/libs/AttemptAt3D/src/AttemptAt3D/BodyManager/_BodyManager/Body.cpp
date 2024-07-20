
#include "AttemptAt3D/BodyManager/_BodyManager/Body.hpp"

#include "AttemptAt3D/Debug/Debug.hpp"

namespace AttemptAt3D::_BodyManager
{
	/* Constructors */

	Body::Body() :
		transform(glm::mat4(1.0f)),
		vao(-1),
		vbo(-1),
		ebo(-1),
		verticesLen(0),
		vertices(nullptr),
		elementsLen(0),
		elements(nullptr)
	{}

	/* Methods */

	void Body::setData(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements)
	{
		this->verticesLen = verticesLen;
		this->vertices = std::move(vertices);
		this->elementsLen = elementsLen;
		this->elements = std::move(elements);
	}

	void Body::initializeVao(ShaderManager& shaderManager)
	{
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);
		
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		glGenBuffers(1, &this->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

		glBufferData(GL_ARRAY_BUFFER, this->verticesLen * sizeof(this->vertices[0]), this->vertices.get(), GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elementsLen * sizeof(this->elements[0]), this->elements.get(), GL_DYNAMIC_DRAW);

		shaderManager.doAttribs();

		glBindVertexArray(0);
	}

	float TEMP_calculateDeltaTime()
	{
		using std::chrono::steady_clock;
		using std::chrono::duration;

		static steady_clock::time_point timePoint = steady_clock::now();
		steady_clock::time_point oldTimePoint = timePoint;
		timePoint = steady_clock::now();

		duration<float> timeElapsed = std::chrono::duration_cast<duration<float>>(timePoint - oldTimePoint);
		return timeElapsed.count();
	}

	void Body::drawBody(ShaderManager& shaderManager)
	{
		glBindVertexArray(this->vao);

		{
			// static float cumlTime = 0.0f;
			// cumlTime += TEMP_calculateDeltaTime();

			float deltaTime = TEMP_calculateDeltaTime();

			if (this->vao == 1)
			{
				glm::quat quatZ = glm::angleAxis(-0.9f * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
				glm::mat4 rotZ = glm::toMat4(quatZ);

				this->transform = rotZ * this->transform;
			}
			else
			{
				glm::quat quatZ = glm::angleAxis(0.9f * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
				glm::mat4 rotZ = glm::toMat4(quatZ);

				this->transform = rotZ * this->transform;
			}
		}

		shaderManager.change_uni_modelVal(this->transform);
		glDrawElements(GL_TRIANGLES, this->elementsLen, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void Body::cleanupForGl()
	{
		glDeleteBuffers(1, &this->ebo);
		glDeleteBuffers(1, &this->vbo);
		glDeleteVertexArrays(1, &this->vao);
	}
}
