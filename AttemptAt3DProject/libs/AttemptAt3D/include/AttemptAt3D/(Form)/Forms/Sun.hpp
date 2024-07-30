
#pragma once

#include "AttemptAt3D/(Form)/Form.hpp"

namespace AttemptAt3D::Forms
{
	class Sun : public Form
	{
		/* Constructors */

		using Form::Form;

	   protected:
		template <class T, typename std::enable_if<std::is_base_of<Sun, T>::value>::type* = nullptr>
		static inline std::unique_ptr<T> New(WorldState& worldState)
		{ return Form::New<T>(worldState); }

	   public:
		static inline std::unique_ptr<Sun> New(WorldState& worldState)
		{ return Sun::New<Sun>(worldState); }

		/* Fields */

	   public:
		float brightness;

		/* Methods */

	   public:
		void recalculateAndApplyViewMatrix(WorldState& worldState);

	   protected:
		void onCreate_(WorldState& worldState) final;
		void onUpdate_(WorldState& worldState, float deltaTime) final;
		virtual void onCreate__(WorldState& worldState) {};
		virtual void onUpdate__(WorldState& worldState, float deltaTime) {};

		/* Friends */

		friend std::unique_ptr<Sun> std::make_unique<Sun>(AttemptAt3D::WorldState&);
	};
}
