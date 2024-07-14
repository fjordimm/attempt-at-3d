
#pragma once

#include <string>

namespace AttemptAt3D::FileLoading
{
	// Responsibility of the receiver to free the string returned
	const char* loadFile(const char* name);
}
