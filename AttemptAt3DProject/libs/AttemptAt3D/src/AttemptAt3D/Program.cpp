
#include "AttemptAt3D/Head.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/Sphere.hpp"

int main(void)
{
	// AttemptAt3D::Debug::Printf("%s\n", AttemptAt3D::MeshSamples::Sphere<3>().make()->toString().c_str());

	AttemptAt3D::Head head;
	head.start(1300, 750);
	
	return 0;
}
