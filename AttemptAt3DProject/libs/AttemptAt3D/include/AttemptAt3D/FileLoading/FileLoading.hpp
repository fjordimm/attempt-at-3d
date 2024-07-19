
#pragma once

#include <memory>
#include <string>

namespace AttemptAt3D::FileLoading
{
	std::unique_ptr<const std::string> LoadFile(const std::string name);
}
