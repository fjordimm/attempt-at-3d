
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <list>
#include <memory>
#include "AttemptAt3D/BodyManager/_BodyManager/Body.hpp"

namespace AttemptAt3D
{
	class BodyReference
	{
		friend class BodyManager;

		/* Fields */

	   private:
		_BodyManager::Body* const bodyPtr;
		std::list<std::unique_ptr<_BodyManager::Body>>::const_iterator iter; // since there is no way to get a node for std::list, I use an iterator with the cursor at the current element which has the same functionality

		/* Constructors */

	   public:
		BodyReference(const BodyReference&) = delete;
		BodyReference& operator=(const BodyReference&) = delete;
		
		BodyReference(_BodyManager::Body* bodyPtr);

		/* Getters and Setters */

		inline glm::mat4& access_bodyTransform() { return this->bodyPtr->transform; }
	};
}
