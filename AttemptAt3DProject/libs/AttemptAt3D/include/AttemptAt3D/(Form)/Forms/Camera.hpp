
#pragma once

#include "AttemptAt3D/(Form)/PhysicForm.hpp"

namespace AttemptAt3D::Forms
{
	class Camera : public PhysicForm
	{
		/* Constructors */

		using PhysicForm::PhysicForm;

	   protected:
		template <class T, typename std::enable_if<std::is_base_of<Camera, T>::value>::type* = nullptr>
		static inline std::unique_ptr<T> New(WorldState& worldState)
		{ return PhysicForm::New<T>(worldState, nullptr); }

	   public:
		static inline std::unique_ptr<Camera> New(WorldState& worldState)
		{ return Camera::New<Camera>(worldState); }

		/* Methods */

	   public:
		void recalculateAndApplyViewMatrix(ShaderManager& shaderManager);

	   protected:
		void onCreate__(WorldState& worldState) final;
		void onUpdate__(WorldState& worldState, float deltaTime) final;
		virtual void onCreate___(WorldState& worldState) {};
		virtual void onUpdate___(WorldState& worldState, float deltaTime) {};

		/* Friends */

		friend std::unique_ptr<Camera> std::make_unique<Camera>(AttemptAt3D::WorldState&, AttemptAt3D::Mesh*&);
	};
}
