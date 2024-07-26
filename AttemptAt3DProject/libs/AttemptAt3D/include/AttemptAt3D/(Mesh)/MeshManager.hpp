
#pragma once

#include <unordered_map>
#include <memory>
#include "AttemptAt3D/(Mesh)/Mesh.hpp"

namespace AttemptAt3D
{
	class MeshManager
	{
		/* Constructors */

	   public:
		MeshManager(const MeshManager&) = delete;
		MeshManager& operator=(const MeshManager&) = delete;
		
		MeshManager();
		
		/* Fields */

	   private:
		std::unordered_map<Mesh*, std::unique_ptr<Mesh>> meshes;

		/* Methods */

	   public:
		Mesh* add(std::unique_ptr<Mesh> mesh);
		void remove(Mesh* mesh);
	};
}
