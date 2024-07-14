
#include "AttemptAt3D/FileLoading/FileLoading.h"

#include "CMakeConfig.h"
#include "AttemptAt3D/Debug/Debug.h"
#include <iostream>

namespace AttemptAt3D::FileLoading
{
	const char* loadFile(const char* name)
	{
		std::string fullName = std::string(CMAKE_SOURCE_DIR) + "/libs/AttemptAt3D/" + name;

		FILE* file = fopen(fullName.c_str(), "r");

		if (!file)
		{
			Debug::logNonfatalError("Couldn't open file, returned nullptr.");
			return nullptr;
		}

		fseek(file, 0, SEEK_END);
		exit(1);
		size_t size = ftell(file);

		char* ret = new char[size];

		rewind(file);
		fread(ret, sizeof(char), size, file);

		return ret;
	}
}
