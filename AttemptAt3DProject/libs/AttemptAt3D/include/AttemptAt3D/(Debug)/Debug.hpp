
#pragma once

#include <mutex>

namespace AttemptAt3D::Debug
{
	namespace _Globals
	{
		static std::mutex _GlobalMutex_debug;
	}
}

#include "AttemptAt3D/(Debug)/_logging.hpp"
