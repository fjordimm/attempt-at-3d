
#pragma once

#include <memory>
#include "AttemptAt3D/(Tran)/Tran.hpp"
#include "AttemptAt3D/(Drawing)/MeshManager.hpp"
#include "AttemptAt3D/(Drawing)/ShaderManager.hpp"
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
		
		Form(WorldState& worldState, Mesh* mesh);

	   protected:
		template <class T, typename std::enable_if<std::is_base_of<Form, T>::value>::type* = nullptr>
		static std::unique_ptr<T> New(WorldState& worldState, Mesh* mesh)
		{
			std::unique_ptr<T> ret = std::make_unique<T>(worldState, mesh);
			ret->onCreate(worldState);
			return std::move(ret);
		}

	   public:
		static inline std::unique_ptr<Form> New(WorldState& worldState, Mesh* mesh)
		{ return Form::New<Form>(worldState, mesh); }

		/* Fields */

	   public:
		Tran tran;
		Mesh* mesh;

		/* Methods */

	   public:
		void draw(ShaderManager& shaderManager);

	   private:
		void onCreate(WorldState& worldState);
	   public:
		void onUpdate(WorldState& worldState, float deltaTime);

	   protected:
		virtual void onCreate_(WorldState& worldState) {}
		virtual void onUpdate_(WorldState& worldState, float deltaTime) {}

		/* Friends */

		friend std::unique_ptr<Form> std::make_unique<Form>(AttemptAt3D::WorldState&, AttemptAt3D::Mesh*&);

		// TODO: call cleanupForGl() for each DrawObj
	};
}
