
#include "AttemptAt3D/Debug/Debug_logging.h"

#include <cstdio>
#include <cstdlib>

namespace AttemptAt3D::Debug
{
	void log(const char* msg)
	{
		std::fprintf(stderr, "===DEBUG===: %s\n", msg);
	}

	void logWarning(const char* msg)
	{
		std::fprintf(stderr, "===WARNING===: %s\n", msg);
	}

	void logNonfatalError(const char* msg)
	{
		std::fprintf(stderr, "===NONFATAL ERROR===: %s\n", msg);
	}

	void logFatalError(const char* msg)
	{
		std::fprintf(stderr, "===FATAL ERROR===: %s\n", msg);
		std::exit(EXIT_FAILURE);
	}
}
