
#include "AttemptAt3D/BodyManager/BodyManager.h"

namespace AttemptAt3D
{
	using BodyReference = BodyManager::BodyReference;
	using Body = _BodyManager::Body;

	BodyManager::BodyManager() {}

	BodyManager::~BodyManager() {}

	std::unique_ptr<BodyReference> BodyManager::makeNewBody(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements)
	{
		this->bodies.push_back({});
		this->bodies.back().setData(verticesLen, std::move(vertices), elementsLen, std::move(elements));

		std::unique_ptr<BodyReference> ret = std::make_unique<BodyReference>();
		ret->iter = this->bodies.end();
		ret->iter--; // sets it to the actual end

		return ret;
	}

	void BodyManager::removeBody(std::unique_ptr<BodyReference> bodyReference)
	{
		this->bodies.erase(bodyReference->iter);
	}

	void BodyManager::drawAllBodies()
	{
		
	}

	/* BodyReference class */
	
	BodyReference::BodyReference() {}

	BodyReference::~BodyReference() {}
}
