
#pragma once

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
	#ifdef ATTEMPTAT3D_DO_ASSERTIONS
		#define ATTEMPTAT3D_DEBUG_ASSERT(Expr) AttemptAt3D::Debug::_Assert(Expr)
	#else
		#define ATTEMPTAT3D_DEBUG_ASSERT(Expr) (void)0
	#endif
}
