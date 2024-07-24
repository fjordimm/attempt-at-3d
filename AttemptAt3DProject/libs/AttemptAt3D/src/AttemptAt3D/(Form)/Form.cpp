
#include "AttemptAt3D/(Form)/Form.hpp"

#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	Form::Form(ShaderManager& shaderManager, std::unique_ptr<Mesh> mesh) :
		tran(),
		mesh(std::move(mesh)),
		drawObj(shaderManager, &this->tran, this->mesh.get())
	{}

	// std::unique_ptr<Form> Form::New(ShaderManager& shaderManager, std::unique_ptr<Mesh> mesh)
	// {
	// 	std::unique_ptr<Form> ret = std::make_unique<Form>(shaderManager, std::move(mesh));
	// }

	/* Methods */

	void Form::draw(ShaderManager& shaderManager) const
	{
		this->drawObj.draw(shaderManager);
	}

	// void onCreate()
}
