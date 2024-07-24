
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

	//    public:
	// 	static std::unique_ptr<Form> New(ShaderManager& shaderManager, std::unique_ptr<Mesh> mesh);

		/* Fields */

	   public:
		Tran tran;
		std::unique_ptr<Mesh> mesh;

	   private:
		DrawObj drawObj;

		/* Methods */

	   public:
		void draw(ShaderManager& shaderManager) const;

	//    private:
	// 	void onCreate();
	//    public:
	// 	void onUpdate();

	//    private:
	// 	virtual void onCreate_child() {}
	// 	virtual void onUpdate_child() {}

		// TODO: call cleanupForGl() for each DrawObj
	};
}
