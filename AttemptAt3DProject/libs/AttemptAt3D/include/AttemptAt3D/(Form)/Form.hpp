
#pragma once

#include <memory>
#include "AttemptAt3D/(Tran)/Tran.hpp"
#include "AttemptAt3D/(Mesh)/Mesh.hpp"
#include "AttemptAt3D/(DrawObj)/DrawObj.hpp"

namespace AttemptAt3D
{
	class Form
	{
		/* Constructors */

	   public:
		Form() = delete;
		Form(const Form&) = delete;
		Form& operator=(const Form&) = delete;
		
		Form(ShaderManager& shaderManager, std::unique_ptr<Mesh> mesh);

		/* Fields */

	   public:
		Tran tran;
		std::unique_ptr<Mesh> mesh;

	   private:
		DrawObj drawObj;

		/* Methods */

	   public:
		void draw(ShaderManager& shaderManager) const;

		// TODO: call cleanupForGl() for each DrawObj
	};
}
