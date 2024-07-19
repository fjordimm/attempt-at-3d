
#pragma once

#include <mutex>

namespace AttemptAt3D::Debug
{
	namespace _Globals
	{
		static std::mutex _globalMutex_Debug;
	}
}

#include "AttemptAt3D/Debug/Debug_logging.hpp"
