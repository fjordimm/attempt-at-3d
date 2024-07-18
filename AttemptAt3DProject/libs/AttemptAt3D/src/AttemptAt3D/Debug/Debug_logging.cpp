
#include "AttemptAt3D/Debug/Debug_logging.h"

#include <cstdio>
#include <cstdlib>
#include <mutex>

namespace AttemptAt3D::Debug
{
	static std::mutex _Mutex_Debug;

	void Log(const char* msg)
	{
		std::lock_guard<std::mutex> _lock(_Mutex_Debug);

		std::fprintf(stderr, "===DEBUG===: %s\n", msg);
	}

	void LogWarning(const char* msg)
	{
		std::lock_guard<std::mutex> _lock(_Mutex_Debug);

		std::fprintf(stderr, "===WARNING===: %s\n", msg);
	}

	void LogNonfatalError(const char* msg)
	{
		std::lock_guard<std::mutex> _lock(_Mutex_Debug);

		std::fprintf(stderr, "===NONFATAL ERROR===: %s\n", msg);
	}

	void LogFatalError(const char* msg)
	{
		std::lock_guard<std::mutex> _lock(_Mutex_Debug);
		
		std::fprintf(stderr, "===FATAL ERROR===: %s\n", msg);
		std::exit(EXIT_FAILURE);
	}
}
