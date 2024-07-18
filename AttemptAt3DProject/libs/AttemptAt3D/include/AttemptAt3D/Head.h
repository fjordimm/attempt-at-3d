
#pragma once

#include "AttemptAt3D/BodyManager/BodyManager.h"

namespace AttemptAt3D
{
	class Head
	{
		/* Fields */

	   private:
		BodyManager bodyManager;

		/* Getters and Setters */

	   public:
		inline BodyManager& get_bodyManager() { return this->bodyManager; }

		/* Constructors */

	   public:
		Head();
		~Head();
		Head(const Head&) = delete;
		Head& operator=(const Head&) = delete;
		Head(Head&&) {}

		/* Methods */

	   public:
		void start();
	
	   private:
		void mainLoop();
	};
}
