
#include "AttemptAt3D/BodyManager/BodyManager.hpp"

#include <cstdio>
#include <iostream>
#include "AttemptAt3D/Debug/Debug.hpp"

namespace AttemptAt3D
{
	using BodyReference = BodyManager::BodyReference;
	using Body = _BodyManager::Body;

	/* Constructors */

	BodyManager::BodyManager() :
		bodies()
	{}

	BodyManager::~BodyManager()
	{
		this->bodies.clear();
	}

	/* Methods */

	std::unique_ptr<BodyReference> BodyManager::addNewBody(std::size_t verticesLen, std::unique_ptr<float[]> vertices, std::size_t elementsLen, std::unique_ptr<GLuint[]> elements)
	{
		this->bodies.push_back({});
		this->bodies.back().setData(verticesLen, std::move(vertices), elementsLen, std::move(elements));

		std::unique_ptr<BodyReference> ret = std::make_unique<BodyReference>();
		ret->iter = this->bodies.cend();
		ret->iter--; // sets it to the actual end

		return ret;
	}

	void BodyManager::removeBody(std::unique_ptr<BodyReference> bodyReference)
	{
		this->bodies.erase(bodyReference->iter);
	}

	void BodyManager::drawAllBodies()
	{
		for (Body& body : this->bodies)
		{
			std::printf("Body:\n");

			std::printf("  vertices:\n");
			for (int i = 0; i < body.get_verticesLen(); i++)
			{
				std::printf("    %f\n", body.get_vertices()[i]);
			}

			std::printf("  elements:\n");
			for (int i = 0; i < body.get_elementsLen(); i++)
			{
				std::printf("    %u\n", body.get_elements()[i]);
			}
		}
	}

	/* Subclasses */

	/// BodyReference ///
	////////////////////////////////////////////////////////////
		/* Constructors */

		BodyReference::BodyReference() :
			iter{}
		{}
	////////////////////////////////////////////////////////////
}
