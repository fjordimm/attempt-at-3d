
#pragma once

#include <unordered_map>
#include <memory>
#include "AttemptAt3D/(Drawing)/(Meshes)/Mesh.hpp"
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderProgram.hpp"

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
		Mesh* add(ShaderProgram& shaderProgram, std::unique_ptr<MeshData> meshData); // Only to be used after the main loop has started
		void remove(Mesh* mesh);
	};
}
