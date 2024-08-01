
#pragma once

#include "CMakeConfig.h"

namespace AttemptAt3D::Debug
{
	void Log(const char* msg);
	void LogWarning(const char* msg);
	void LogNonfatalError(const char* msg);
	void LogFatalError(const char* msg);
	void Printf(char const* const format, ...);
	void Logf(char const* const format, ...);
	void Exit();

	void _Assert(bool expr);
	#ifdef CMAKECONFIG_DO_ASSERTIONS
		#define ATTEMPTAT3D_DEBUG_ASSERT(Expr) AttemptAt3D::Debug::_Assert(Expr)
	#else
		#define ATTEMPTAT3D_DEBUG_ASSERT(Expr) AttemptAt3D::Debug::Log("howeiieieie")
	#endif
}
