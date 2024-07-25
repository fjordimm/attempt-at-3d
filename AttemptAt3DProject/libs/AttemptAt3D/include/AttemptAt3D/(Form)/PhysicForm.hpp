
#pragma once

#include "AttemptAt3D/(Form)/Form.hpp"

namespace AttemptAt3D
{
	class PhysicForm : public Form
	{
		/* Constructors */

		using Form::Form;

	   protected:
		template <class T, typename std::enable_if<std::is_base_of<PhysicForm, T>::value>::type* = nullptr>
		static inline std::unique_ptr<T> New(WorldState& worldState, std::unique_ptr<Mesh> mesh)
		{ return Form::New<T>(worldState, std::move(mesh)); }

	   public:
		static inline std::unique_ptr<PhysicForm> New(WorldState& worldState, std::unique_ptr<Mesh> mesh)
		{ return PhysicForm::New<PhysicForm>(worldState, std::move(mesh)); }
		
		/* Fields */

	   public:
		Vec velocity;
		Vec rotationVelocityAxis;
		float rotationVelocityRadians;

		/* Methods */

	   protected:
		void onCreate_(WorldState& worldState) final;
		void onUpdate_(WorldState& worldState, float deltaTime) final;
		virtual void onCreate__(WorldState& worldState) {};
		virtual void onUpdate__(WorldState& worldState, float deltaTime) {};

		/* Friends */

		friend std::unique_ptr<PhysicForm> std::make_unique<PhysicForm>(AttemptAt3D::WorldState&, std::unique_ptr<AttemptAt3D::Mesh>&&);
	};
}
