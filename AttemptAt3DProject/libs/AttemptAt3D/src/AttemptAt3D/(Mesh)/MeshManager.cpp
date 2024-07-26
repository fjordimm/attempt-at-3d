
#include "AttemptAt3D/(Mesh)/MeshManager.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	MeshManager::MeshManager() :
		meshes()
	{}

	/* Methods */

	Mesh* MeshManager::add(std::unique_ptr<Mesh> mesh)
	{
		Mesh* ret = mesh.get();
		this->meshes[ret] = std::move(mesh);
		return ret;
	}

	void MeshManager::remove(Mesh* mesh)
	{

	}
}
