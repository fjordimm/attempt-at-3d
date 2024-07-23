
#include "AttemptAt3D/(Debug)/Debug.hpp"
#include "AttemptAt3D/(Debug)/_logging.hpp"

#include <cstdio>
#include <cstdarg>
#include <cstdlib>

namespace AttemptAt3D::Debug
{
	void Log(const char* msg)
	{
		std::lock_guard<std::mutex> _lock(_Globals::_GlobalMutex_debug);

		std::fprintf(stderr, "===DEBUG===: %s\n", msg);
		std::fflush(stderr);
	}

	void LogWarning(const char* msg)
	{
		std::lock_guard<std::mutex> _lock(_Globals::_GlobalMutex_debug);

		std::fprintf(stderr, "===WARNING===: %s\n", msg);
		std::fflush(stderr);
	}

	void LogNonfatalError(const char* msg)
	{
		std::lock_guard<std::mutex> _lock(_Globals::_GlobalMutex_debug);

		std::fprintf(stderr, "===NONFATAL ERROR===: %s\n", msg);
		std::fflush(stderr);
	}

	void LogFatalError(const char* msg)
	{
		std::lock_guard<std::mutex> _lock(_Globals::_GlobalMutex_debug);
		
		std::fprintf(stderr, "===FATAL ERROR===: %s\n", msg);
		std::fflush(stderr);
		std::exit(EXIT_FAILURE);
	}

	void Printf(char const* const format, ...)
	{
		std::lock_guard<std::mutex> _lock(_Globals::_GlobalMutex_debug);

		std::va_list argptr;
		va_start(argptr, format);
		std::vfprintf(stderr, format, argptr);
		std::fflush(stderr);
		va_end(argptr);
	}

	void Logf(char const* const format, ...)
	{
		std::lock_guard<std::mutex> _lock(_Globals::_GlobalMutex_debug);

		std::va_list argptr;
		va_start(argptr, format);
		std::fprintf(stderr, "===DEBUG===: ");
		std::vfprintf(stderr, format, argptr);
		std::fprintf(stderr, "\n");
		std::fflush(stderr);
		va_end(argptr);
	}

	void Exit()
	{
		std::lock_guard<std::mutex> _lock(_Globals::_GlobalMutex_debug);

		std::fprintf(stderr, "===EXITING===\n");
		std::fflush(stderr);
		std::exit(EXIT_FAILURE);
	}
}
