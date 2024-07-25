
#pragma once

#include <memory>
#include "AttemptAt3D/(Tran)/Tran.hpp"
#include "AttemptAt3D/(Mesh)/Mesh.hpp"
#include "AttemptAt3D/(DrawObj)/DrawObj.hpp"
#include "AttemptAt3D/(ShaderManager)/ShaderManager.hpp"
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
		
		Form(WorldState& worldState, std::unique_ptr<Mesh> mesh);

	   public:
		template <class T = Form, typename std::enable_if<std::is_base_of<Form, T>::value>::type* = nullptr>
		static std::unique_ptr<T> New(WorldState& worldState, std::unique_ptr<Mesh> mesh)
		{
			std::unique_ptr<T> ret = std::make_unique<T>(worldState, std::move(mesh));
			ret->onCreate(worldState);
			return std::move(ret);
		}

		/* Fields */

	   public:
		Tran tran;
		std::unique_ptr<Mesh> mesh;

	   private:
		DrawObj drawObj;

		/* Methods */

	   public:
		void draw(ShaderManager& shaderManager) const;

	   private:
		void onCreate(WorldState& worldState);
	   public:
		void onUpdate(WorldState& worldState, float deltaTime);

	   private:
		virtual void onCreate_child(WorldState& worldState) {}
		virtual void onUpdate_child(WorldState& worldState, float deltaTime) {}

		/* Friends */

		friend std::unique_ptr<Form> std::make_unique<Form>(AttemptAt3D::WorldState&, std::unique_ptr<AttemptAt3D::Mesh>&&);

		// TODO: call cleanupForGl() for each DrawObj
	};
}
