
#pragma once

#include <memory>
#include "AttemptAt3D/(Trans)/Trans.hpp"
#include "AttemptAt3D/(Mesh)/Mesh.hpp"
#include "AttemptAt3D/(BodyManager)/BodyManager.hpp"
#include "AttemptAt3D/(BodyManager)/BodyReference.hpp"

namespace AttemptAt3D
{
	class Form
	{
		/* Constructors */

	   public:
		Form() = delete;
		Form(const Form&) = delete;
		Form& operator=(const Form&) = delete;
		
		Form(ShaderManager& shaderManager, BodyManager& bodyManager, const Trans& trans, std::unique_ptr<Mesh> mesh);

		/* Fields */

	   public:
		Trans trans;
		std::unique_ptr<Mesh> mesh;

	   private:
		std::unique_ptr<BodyReference> bodyReference;
	};
}
