
#pragma once

#include <memory>
#include "AttemptAt3D/(Tran)/Tran.hpp"
#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderProgram.hpp"
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshManager.hpp"
#include "AttemptAt3D/WorldState.hpp"

namespace AttemptAt3D
{
	class Form
	{
		/* Constructors */

	   protected:
		Form() = delete;
		Form(const Form&) = delete;
		Form& operator=(const Form&) = delete;
		
		Form(WorldState& worldState);

	   protected:
		template <class T, typename std::enable_if<std::is_base_of<Form, T>::value>::type* = nullptr>
		static std::unique_ptr<T> New(WorldState& worldState)
		{
			std::unique_ptr<T> ret = std::make_unique<T>(worldState);
			ret->onCreate(worldState);
			return std::move(ret);
		}

	   public:
		static inline std::unique_ptr<Form> New(WorldState& worldState)
		{ return Form::New<Form>(worldState); }

		/* Fields */

	   public:
		Tran tran;
		Mesh* mesh;

	   private:
		ShaderProgram* shaderProgram;
		std::list<std::tuple<Mesh*, Tran*>>::const_iterator shaderProgramSpot;

		/* Methods */

	   public:
		void setMeshAndLinkToShaderProgram(ShaderProgram* newShaderProgram, Mesh* mesh);

	   private:
		void onCreate(WorldState& worldState);
	   public:
		void onUpdate(WorldState& worldState, float deltaTime);

	   protected:
		virtual void onCreate_(WorldState& worldState) {}
		virtual void onUpdate_(WorldState& worldState, float deltaTime) {}

		/* Friends */

		friend std::unique_ptr<Form> std::make_unique<Form>(AttemptAt3D::WorldState&);

		// TODO: do ShaderProgram.removeForm() when Form is removed

		// TODO: call cleanupForGl() for each DrawObj
	};
}
