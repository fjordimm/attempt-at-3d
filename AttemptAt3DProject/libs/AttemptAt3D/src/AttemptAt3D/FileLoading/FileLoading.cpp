
#include "AttemptAt3D/FileLoading/FileLoading.hpp"

#include <iostream>
#include <fstream>
#include "CMakeConfig.h"
#include "AttemptAt3D/Debug/Debug.hpp"

namespace AttemptAt3D::FileLoading
{
	std::unique_ptr<const std::string> LoadFile(const std::string name)
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

		char* buf = new char[size + 1];

		size_t charsRead = fread(buf, sizeof(char), size, file);
		buf[charsRead] = '\0';

		fclose(file);

		std::unique_ptr<const std::string> ret(new const std::string(buf));
		return std::move(ret);
	}
}
