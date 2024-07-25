
#pragma once

#include "AttemptAt3D/(Form)/Form.hpp"

namespace AttemptAt3D::Forms
{
	class Camera : public Form
	{
		/* Constructors */

		using Form::Form;

	   protected:
		template <class T, typename std::enable_if<std::is_base_of<Camera, T>::value>::type* = nullptr>
		static std::unique_ptr<T> New(WorldState& worldState)
		{
			return Form::New<T>(worldState, nullptr);
		}

	   public:
		static inline std::unique_ptr<Camera> New(WorldState& worldState)
		{ return Camera::New<Camera>(worldState); }

		/* Methods */

	   public:
		void recalculateAndApplyViewMatrix(ShaderManager& shaderManager);

		/* Friends */

		friend std::unique_ptr<Camera> std::make_unique<Camera>(AttemptAt3D::WorldState&, std::unique_ptr<AttemptAt3D::Mesh>&&);
	};
}
