
#include "AttemptAt3D/Debug/Debug_logging.h"

#include <cstdio>
#include <cstdlib>
#include <mutex>

namespace AttemptAt3D::Debug
{
	static std::mutex _GlobalMutex_debugPrinting;

	void Log(const char* msg)
	{
		std::fprintf(stderr, "===DEBUG===: %s\n", msg);
	}

	void LogWarning(const char* msg)
	{
		std::fprintf(stderr, "===WARNING===: %s\n", msg);
	}

	void LogNonfatalError(const char* msg)
	{
		std::fprintf(stderr, "===NONFATAL ERROR===: %s\n", msg);
	}

	void LogFatalError(const char* msg)
	{
		std::fprintf(stderr, "===FATAL ERROR===: %s\n", msg);
		std::exit(EXIT_FAILURE);
	}
}
