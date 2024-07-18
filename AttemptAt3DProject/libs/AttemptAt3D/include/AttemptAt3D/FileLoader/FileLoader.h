
#pragma once

#include <string>

namespace AttemptAt3D::FileLoader
{
	// Responsibility of the receiver to free the string returned
	const char* LoadFile(const char* name);
}
