
#pragma once

#include <list>
#include <memory>
#include "AttemptAt3D/(headerGroups)/glmGroup.hpp"
#include "AttemptAt3D/(BodyManager)/_BodyManager/Body.hpp"

namespace AttemptAt3D
{
	class BodyReference
	{
		friend class BodyManager;

		/* Constructors */

	   public:
		BodyReference(const BodyReference&) = delete;
		BodyReference& operator=(const BodyReference&) = delete;
		
		BodyReference(_BodyManager::Body* bodyPtr);

		/* Fields */

	   private:
		_BodyManager::Body* const bodyPtr;
		std::list<std::unique_ptr<_BodyManager::Body>>::const_iterator iter; // since there is no way to get a node for std::list, I use an iterator with the cursor at the current element which has the same functionality
	};
}