
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AttemptAt3D/BodyManager/Body.h"

namespace AttemptAt3D
{
	class BodyManager
	{
	public:
		BodyManager();
		~BodyManager();
		BodyManager(const BodyManager&) = delete;
		BodyManager& operator=(const BodyManager&) = delete;
	
	private:
	};
}
