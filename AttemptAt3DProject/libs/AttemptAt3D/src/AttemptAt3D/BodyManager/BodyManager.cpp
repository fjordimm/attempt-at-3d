
#include "AttemptAt3D/BodyManager/BodyManager.hpp"

#include <cstdio>
#include <iostream>
#include "AttemptAt3D/Debug/Debug.hpp"

namespace AttemptAt3D
{
	using Body = _BodyManager::Body;

	/* Constructors */

	BodyManager::BodyManager() :
		bodies()
	{}

	/* Methods */

	std::unique_ptr<BodyReference> BodyManager::addNewBody(ShaderManager& shaderManager, std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements)
	{
		std::unique_ptr<Body> body = std::make_unique<Body>();
		body->setData(verticesLen, std::move(vertices), elementsLen, std::move(elements));
		body->initializeVao(shaderManager);
		this->bodies.push_back(std::move(body));

		std::unique_ptr<BodyReference> ret = std::make_unique<BodyReference>(&*(this->bodies.back()));
		ret->iter = this->bodies.cend();
		ret->iter--; // sets it to the actual end

		return ret;
	}

	void BodyManager::removeBody(std::unique_ptr<BodyReference> bodyReference)
	{
		this->bodies.erase(bodyReference->iter);
	}

	void BodyManager::drawAllBodies(ShaderManager& shaderManager)
	{
		for (std::unique_ptr<Body>& body_ : this->bodies)
		{
			Body* body = &*body_;
			
			body->drawBody(shaderManager);
		}
	}

	void BodyManager::cleanupForGl()
	{
		for (std::unique_ptr<Body>& body_ : this->bodies)
		{
			Body* body = &*body_;

			body->cleanupForGl();
		}
	}
}
