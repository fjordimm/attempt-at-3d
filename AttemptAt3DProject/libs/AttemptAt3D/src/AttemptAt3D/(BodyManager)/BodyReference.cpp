
#include "AttemptAt3D/(BodyManager)/BodyReference.hpp"

namespace AttemptAt3D
{
	using Body = _BodyManager::Body;

	/* Constructors */

	BodyReference::BodyReference(Body* bodyPtr) :
		bodyPtr(bodyPtr),
		iter{}
	{}
}
