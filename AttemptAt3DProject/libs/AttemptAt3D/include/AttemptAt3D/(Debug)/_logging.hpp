
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
}
