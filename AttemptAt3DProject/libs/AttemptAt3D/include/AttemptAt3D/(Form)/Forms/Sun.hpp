
#pragma once

#include "AttemptAt3D/(Form)/Form.hpp"
#include "AttemptAt3D/(Util)/(Color)/Color.hpp"

namespace AttemptAt3D::Forms
{
	class Sun : public Form
	{
		/* Constructors */

	   protected:
		Sun() = delete;
		Sun(const Sun&) = delete;
		Sun& operator=(const Sun&) = delete;

		Sun(WorldState& worldState);

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
		float ambientLight;
		Color color;

		/* Methods */

	   public:
		void recalculateAndApplySunRotMatrix(WorldState& worldState);
		
	   protected:
		void onCreate_(WorldState& worldState) final;
		void onUpdate_(WorldState& worldState, float deltaTime) final;
		virtual void onCreate__(WorldState& worldState) {};
		virtual void onUpdate__(WorldState& worldState, float deltaTime) {};

		/* Friends */

		friend std::unique_ptr<Sun> std::make_unique<Sun>(AttemptAt3D::WorldState&);
	};
}
