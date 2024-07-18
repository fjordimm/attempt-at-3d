
#include "AttemptAt3D/FileLoading/FileLoading.h"

#include "CMakeConfig.h"
#include "AttemptAt3D/Debug/Debug.h"
#include <iostream>
#include <fstream>

namespace AttemptAt3D::FileLoading
{
	const char* LoadFile(const char* name)
	{
		std::string fullName = std::string(CMAKE_SOURCE_DIR) + "/libs/AttemptAt3D/" + name;

		FILE* file = fopen(fullName.c_str(), "r");

		if (!file)
		{
			Debug::LogNonfatalError("Couldn't open file, returned nullptr.");
			return nullptr;
		}

		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		fseek(file, 0, SEEK_SET);

		char* ret = new char[size + 1];

		size_t charsRead = fread(ret, sizeof(char), size, file);
		ret[charsRead] = '\0';

		fclose(file);
		return ret;
	}
}
