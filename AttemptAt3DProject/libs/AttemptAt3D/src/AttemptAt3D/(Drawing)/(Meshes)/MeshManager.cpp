
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshManager.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	MeshManager::MeshManager() :
		meshes()
	{}

	/* Methods */

	Mesh* MeshManager::add(ShaderProgram& shaderProgram, std::unique_ptr<MeshData> meshData)
	{
		std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>(std::move(meshData));
		mesh->generateGlVaoAndBuffers();
		shaderProgram.enableAttribsForMesh();
		mesh->updateGlBufferData();

		Mesh* ret = mesh.get();
		this->meshes[ret] = std::move(mesh);
		return ret;
	}

	void MeshManager::remove(Mesh* mesh)
	{
		auto iter = this->meshes.find(mesh);
		
		if (iter == this->meshes.end())
		{
			Debug::LogWarning("Tried to remove a non-existant mesh from MeshManager.");
		}
		else
		{
			iter->second.get()->cleanupForGl();
			this->meshes.erase(iter);
		}
	}
}
